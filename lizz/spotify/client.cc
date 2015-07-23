#include "spotify/client.h"

namespace lizz {
namespace spotify {
  
std::shared_ptr<ClientInterface> Client::Login(const std::string& username,
                                               const std::string& password,
                                               std::error_code& err) {
  return std::make_shared<Client>();
}
  
}  // namespace spotify
}  // namespace lizz