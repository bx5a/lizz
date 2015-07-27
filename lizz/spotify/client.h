#ifndef LIZZ_SPOTIFY_CLIENT_H_
#define LIZZ_SPOTIFY_CLIENT_H_

#include <string>
#include <memory>
#include <system_error>
#include <cstdint>
#include <functional>

#include "client_interface.h"

namespace lizz {
namespace spotify {
  
class Client : public ClientInterface {
 public:
  using LoginHandler = std::function<void(const std::string& url)>;
  
  Client(std::string client_id,
         std::string client_secret,
         uint16_t redirect_uri_port);
  
  void Login(LoginHandler login_handler,
             uint16_t timeout_seconds,
             std::error_code& err);
  
 private:
  std::string client_id_, client_secret_, code_;
  uint16_t redirect_uri_port_;
};
  
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_CLIENT_H_
