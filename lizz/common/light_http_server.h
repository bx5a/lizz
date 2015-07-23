#ifndef LIZZ_COMMON_LIGHT_HTTP_SERVER_H_
#define LIZZ_COMMON_LIGHT_HTTP_SERVER_H_

#include <system_error>
#include <cstdint>
#include <functional>
#include <thread>

#include <boost/asio.hpp>

namespace lizz {
class LightHttpServer {
 public:
  using Handler = std::function<std::string(const std::string& request,
                                            std::error_code& err)> ;
  LightHttpServer();
  ~LightHttpServer();
  void Start(uint16_t port, std::error_code& err);
  void SetHandler(Handler handler);
  void Stop(std::error_code& err);
  
 private:
  void RunService(std::error_code& err);
  
  Handler handler_;
  std::thread server_thread_;
  boost::asio::io_service io_service_;
  boost::asio::ip::tcp::socket socket_;
  std::shared_ptr<boost::asio::ip::tcp::acceptor> p_acceptor_;
};
}  // namespace lizz

#endif  // LIZZ_COMMON_LIGHT_HTTP_SERVER_H_
