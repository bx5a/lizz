#include "spotify/client.h"

// casablanca header
#include <cpprest/http_client.h>

#include "common/light_http_server.h"

namespace lizz {
namespace spotify {
  
std::shared_ptr<ClientInterface> Client::Login(
    const std::string& username, const std::string& password,
    const std::string& client_id,const std::string& client_secret,
    std::error_code& err) {
  // start a server
  
  // query the login URL
  
  // post username & password
  
  return std::make_shared<Client>();
}
  
}  // namespace spotify
}  // namespace lizz
