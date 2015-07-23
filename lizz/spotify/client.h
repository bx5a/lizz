#ifndef LIZZ_SPOTIFY_CLIENT_H_
#define LIZZ_SPOTIFY_CLIENT_H_

#include <string>
#include <memory>
#include <system_error>

#include "client_interface.h"

namespace lizz {
namespace spotify {
  
class Client : public ClientInterface {
 public:
  static std::shared_ptr<ClientInterface> Login(const std::string& username,
                                                const std::string& password,
                                                std::error_code& err);
};
  
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_CLIENT_H_
