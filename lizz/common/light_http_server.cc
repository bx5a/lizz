#include "common/light_http_server.h"

#include <boost/array.hpp>

#include "common/log.h"
#include "common/error/conversion.h"

namespace lizz {
  
LightHttpServer::LightHttpServer() : socket_(io_service_) {}
  
LightHttpServer::~LightHttpServer() {
  // ask for server to stop
  io_service_.stop();
  // give the thread all the time it needs to stop
  server_thread_.join();
}
  
void LightHttpServer::Start(uint16_t port, std::error_code& err) {
  try {
    // can throw
    p_acceptor_ = std::make_shared<boost::asio::ip::tcp::acceptor>(
        io_service_,
        boost::asio::ip::tcp::endpoint(
            boost::asio::ip::tcp::v4(), port));
    
    auto handler = [this](const boost::system::error_code& ec) {
      if (ec) {
        LOG(debug) << "Request handler called with error: "
                                 << ec.value();
        return;
      }
      boost::system::error_code boost_err;
      // read the content of the request until "\r\n" (end of request)
      boost::asio::streambuf request;
      boost::asio::read_until(socket_, request, "\r\n", boost_err);
      if (boost_err) {
        LOG(debug) << "Error while reading request: "
                                 << boost_err.value();
        return;
      }
      
      std::string string_request((std::istreambuf_iterator<char>(&request)),
                                  std::istreambuf_iterator<char>());
      
      std::error_code local_err;
      if (handler_) {
        std::string string_response = handler_(string_request,
                                               local_err);
        if (local_err) {
          LOG(debug) << "Server request handler failed: "
                                   << local_err.value();
          return;
        }
        std::vector<char> response(string_response.begin(),
                                   string_response.end());
        socket_.write_some(boost::asio::buffer(response),
                           boost_err);
      } else {
        LOG(debug) << "No request handler found. Returning";
      }
    };
    p_acceptor_->async_accept(socket_, handler);
  } catch (boost::system::system_error& exception) {
    FromBoostError(exception.code(), err);
    LOG(debug) << "Exception caught when initializing acceptor: "
                             << err.value();
    return;
  }
  
  // start thread
  server_thread_ = std::thread([this]() {
    std::error_code err;
    RunService(err);
    if (err) {
      LOG(debug) << "Failed to run the service: " << err.value();
      return;
    }
    // log debug server finishes
    LOG(debug) << "Server stopped";
  });
}
  
void LightHttpServer::SetHandler(Handler handler) {
  handler_ = handler;
}
  
void LightHttpServer::Stop(std::error_code& err) {
  io_service_.stop();
}
  
void LightHttpServer::RunService(std::error_code& err) {
  try {
    LOG(debug) << "Starting server";
    io_service_.run();
  } catch (boost::system::system_error& exception) {
    FromBoostError(exception.code(), err);
    LOG(debug) << "Exception caught when running the io_service: "
                             << err.value();
    return;
  }
}
  
}  // namespace lizz
