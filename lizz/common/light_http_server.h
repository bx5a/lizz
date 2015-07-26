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
  using Handler = std::function<std::string(std::string&& request_header,
                                            std::string&& request_content,
                                            std::error_code& err)>;
  ~LightHttpServer();
  void Init(uint16_t port, std::error_code& err);
  void Start();
  void SetHandler(Handler handler);
  void Stop();
  
 private:
  void HandleHttpRequest(
      std::shared_ptr<boost::asio::ip::tcp::socket> p_socket,
      const boost::system::error_code& boost_err);
  void StartAccept();
  
  std::string ReadRequestHeader(
      std::shared_ptr<boost::asio::ip::tcp::socket> p_socket,
      std::error_code& err);
  
  uint64_t GetContentLength(const std::string& request_header,
                            std::error_code& err);
  
  Handler handler_;
  std::thread io_service_thread_;
  boost::asio::io_service io_service_;
  std::shared_ptr<boost::asio::ip::tcp::acceptor> p_acceptor_;
};
  
}  // namespace lizz

#endif  // LIZZ_COMMON_LIGHT_HTTP_SERVER_H_
