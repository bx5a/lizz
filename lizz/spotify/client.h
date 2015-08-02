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
  
class Client : public ClientInterface, public std::enable_shared_from_this<Client> {
 public:
  /**
   * login handler
   * Using the url, it defines how to handle a login action.
   * A common way is to open the address in a browser and follow the steps
   *
   * @param: url is the address of the authorization page.
   */
  using LoginHandler = std::function<void(const std::string& url)>;
  
  /**
   * login completion handler
   * Notifies any error during the login process and gives the reponse to be 
   * sent.
   * An definition should look like:
   *
   * auto login_completion_handler = [](const std::error_code& err) {
   *   if (err) {
   *     return "HTTP/1.1 500 Internal Server Error\r\n\r\n";
   *   }
   *   return "HTTP/1.1 200 OK\r\n\r\n";
   * }
   *
   * @param: err the error obtained
   */
  using LoginCompletionHandler =
      std::function<std::string(const std::error_code& error)>;
  
  
  Client(std::string client_id,
         std::string client_secret,
         uint16_t redirect_uri_port);
  
  /**
   * @brief Logs the user to the server
   *
   * @login_handler
   */
  void Login(LoginHandler login_handler,
             LoginCompletionHandler completion_handler,
             uint16_t timeout_seconds,
             std::error_code& err);
  
  std::shared_ptr<SearchEngineInterface> GetSearchEngine();
  
  void QueryAccessToken(std::string* p_token_type,
                        std::string* p_access_token,
                        std::error_code& err);
  
 private:
  std::string client_id_, client_secret_, code_;
  uint16_t redirect_uri_port_;
};
  
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_CLIENT_H_
