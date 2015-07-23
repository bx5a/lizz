#include "common/light_http_server.h"

#include <boost/array.hpp>

#include "common/error/conversion.h"

namespace lizz {
  
LightHttpServer::LightHttpServer() : socket_(io_service_) {}
  
LightHttpServer::~LightHttpServer() {
  // ask for server to stop
  io_service_.stop();
  // since stop just notifies, we're not sure the thread won't need some more
  // time to stop.
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
        // log error
        return;
      }
      boost::system::error_code boost_err;
      // read the content of the request
      boost::asio::streambuf request;
      boost::asio::read_until(socket_, request, "\r\n", boost_err);
      if (boost_err) {
        return;
      }
      
      std::string string_request((std::istreambuf_iterator<char>(&request)),
                                  std::istreambuf_iterator<char>());
      
      std::error_code local_err;
      if (handler_) {
        std::string string_response = handler_(string_request,
                                               local_err);
        if (local_err) {
          return;
        }
        std::vector<char> response(string_response.begin(),
                                   string_response.end());
        socket_.write_some(boost::asio::buffer(response),
                           boost_err);
      }
    };
    p_acceptor_->async_accept(socket_, handler);
  } catch (boost::system::system_error& exception) {
    FromBoostError(exception.code(), err);
  }
  
  // start thread
  server_thread_ = std::thread([this]() {
    std::error_code err;
    RunService(err);
    if (err) {
      // log error !
    }
    // log debug server finishes
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
    io_service_.run();
  } catch (boost::system::system_error& exception) {
    FromBoostError(exception.code(), err);
  }
}
  
}  // namespace lizz
