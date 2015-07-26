#include "common/light_http_server.h"

#include <boost/array.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

#include "common/log.h"
#include "common/error/conversion.h"

namespace lizz {
  
LightHttpServer::~LightHttpServer() {
  // ask for io_service to stop
  Stop();
  // give the thread all the time it needs to stop
  if (io_service_thread_.joinable()) {
    io_service_thread_.join();
  }
}
  
void LightHttpServer::Init(uint16_t port, std::error_code& err) {
  try {
    // can throw
    p_acceptor_ = std::make_shared<boost::asio::ip::tcp::acceptor>(
      io_service_,
      boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
  } catch (boost::system::system_error& exception) {
    FromBoostError(exception.code(), err);
    LOG(debug) << "Exception caught when initializing acceptor: "
               << err.value() << " " << exception.what();
    return;
  }
}
  
void LightHttpServer::Start() {
  StartAccept();
  
  // start thread
  io_service_thread_ = std::thread([this]() {
    boost::system::error_code boost_err;
    LOG(debug) << "Starting server";
    io_service_.run(boost_err);
    if (boost_err) {
      LOG(debug) << "Server stopped with error: " << boost_err.value()
                 << " " << boost_err.message();
    }
    LOG(debug) << "Server stopped";
  });
}
  
void LightHttpServer::SetHandler(Handler handler) {
  handler_ = handler;
}
  
void LightHttpServer::Stop() {
  io_service_.stop();
}
  
void LightHttpServer::HandleHttpRequest(
    std::shared_ptr<boost::asio::ip::tcp::socket> p_socket,
    const boost::system::error_code& boost_err) {
  
  LOG(debug) << "Request received";
  if (boost_err) {
    LOG(debug) << "Request handler called with error: "
               << boost_err.value()
               << " " << boost_err.message();
    return;
  }
  
  // restart accept
  StartAccept();
  
  std::error_code local_err;
  // Get headers and Content-Length
  auto request_header = ReadRequestHeader(p_socket, local_err);
  if(local_err) {
    LOG(debug) << "Error while reading header: " << local_err.value();
    return;
  }
  auto content_length = GetContentLength(request_header, local_err);
  if(local_err) {
    LOG(debug) << "No Content-Length found: " << local_err.value();
    return;
  }
  
  // wait to receive the whole content
  while (p_socket->available() < content_length) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  
  // read content
  boost::system::error_code local_boost_err;
  std::vector<char> request(static_cast<unsigned int>(content_length));
  if (content_length > 0) {
    p_socket->read_some(boost::asio::buffer(request), local_boost_err);
    if (local_boost_err) {
      LOG(debug) << "Error while reading content: " << local_boost_err.value()
                 << " " << local_boost_err.message();
      return;
    }
  }
  
  // Use handler
  if (handler_) {
    std::string string_response = handler_(std::move(request_header),
                                           std::string(request.data(),
                                                       request.size()),
                                           local_err);
    if (local_err) {
      LOG(debug) << "Server request handler failed: "
                 << local_err.value();
      return;
    }
    std::vector<char> response(string_response.begin(),
                               string_response.end());
    p_socket->write_some(boost::asio::buffer(response),
                       local_boost_err);
    if (local_boost_err) {
      LOG(debug) << "Failed to write response";
    }
  } else {
    LOG(debug) << "No request handler found. Returning";
  }
}
  
void LightHttpServer::StartAccept() {
  // Initialize new acceptor
  auto p_socket = std::make_shared<boost::asio::ip::tcp::socket>(io_service_);
  p_acceptor_->async_accept(*p_socket,
                            std::bind(&LightHttpServer::HandleHttpRequest,
                                      this,
                                      p_socket,
                                      std::placeholders::_1)
                            );
}
  
std::string LightHttpServer::ReadRequestHeader(
    std::shared_ptr<boost::asio::ip::tcp::socket> p_socket,
    std::error_code& err) {
  
  boost::system::error_code boost_err;
  // read the content of the request until "\r\n" (end of request)
  boost::asio::streambuf request_header;
  boost::asio::read_until(*p_socket, request_header, "\r\n\r\n", boost_err);
  if (boost_err) {
    FromBoostError(boost_err, err);
    return "";
  }
  std::string string_header((std::istreambuf_iterator<char>(&request_header)),
                            std::istreambuf_iterator<char>());
  return string_header;
}
  
uint64_t LightHttpServer::GetContentLength(const std::string& request_header,
                                           std::error_code& err) {
  
  // we are looking for Content-length:[value]\r\n
  boost::regex content_length_regex(
      "(.*)(C|c)(ontent-)(L|l)(ength:)(0|[1-9][0-9]*)(.*)");
  boost::match_results<std::string::const_iterator> regex_results;
  uint64_t result = 0;
  if (boost::regex_match(request_header,
                         regex_results,
                         content_length_regex)) {
    try {
      result = boost::lexical_cast<uint64_t>(regex_results[6]);
    } catch (const boost::bad_lexical_cast&) {
      err = std::make_error_code(std::errc::bad_message);
    }
  }
  return result;
}
  
}  // namespace lizz
