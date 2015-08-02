#include "spotify/client.h"

#include <thread>
#include <regex>

#include <cpprest/http_client.h>

#include "spotify/search_engine.h"

#include "common/log.h"
#include "common/light_http_server.h"
#include "common/string.h"

namespace lizz {
namespace spotify {

Client::Client(std::string client_id,
               std::string client_secret,
               uint16_t redirect_uri_port):
  client_id_(std::move(client_id)),
  client_secret_(std::move(client_secret)),
  redirect_uri_port_(std::move(redirect_uri_port)),
  refresh_token_("") {}
  
void Client::Login(LoginHandler login_handler,
                   LoginCompletionHandler completion_handler,
                   uint16_t timeout_seconds,
                   std::error_code& err) {
  // reset the code
  code_ = "";
  // lock mutex
  std::mutex mutex;
  mutex.lock();
  // start a server
  LightHttpServer server;
  server.Init(redirect_uri_port_, err);
  if (err) {
    return;
  }
  auto handler = [&mutex, completion_handler, this](
      std::string&& request_header, std::string&& request_content,
      std::error_code& err){
    
    std::vector<std::string> splitted_header;
    boost::split(splitted_header, request_header, boost::is_any_of("\r\n"));
    
    // looking for GET /?code=[code] HTTP/1.1
    std::regex regex("(GET )(.*)(code=)(.*)( HTTP)(.*)");
    std::cmatch result;
    uint32_t header_index = 0;
    bool found = false;
    while (header_index < splitted_header.size() &&
           !(found = std::regex_match(splitted_header[header_index].c_str(),
                                      result,
                                      regex))) {
      header_index++;
    }
    if (found) {
      LOG(debug) << "Code received: " << result[4];
      code_ = result[4];
    } else {
      err = std::make_error_code(std::errc::bad_message);
    }
    
    // unlock mutex to sync
    mutex.unlock();
    
    return completion_handler(err);
  };
  server.SetHandler(handler);
  server.Start();
  
  // Create the login URL
  utility::string_t redirect_uri("http://localhost:" +
                                 std::to_string(redirect_uri_port_));
  web::http::uri_builder auth_url("https://accounts.spotify.com/authorize");
  auth_url.append_query("client_id", client_id_);
  auth_url.append_query("response_type", "code");
  auth_url.append_query("redirect_uri", redirect_uri);
  
  // query it using the handler
  login_handler(auth_url.to_string());
  
  // lock mutex or timeout
  auto timeout = std::chrono::seconds(timeout_seconds);
  auto waited = std::chrono::milliseconds(0);
  bool is_sync = false;
  while (timeout > waited && !(is_sync = mutex.try_lock())) {
    auto sleep_time = std::chrono::milliseconds(50);
    std::this_thread::sleep_for(sleep_time);
    waited += sleep_time;
  }
  
  mutex.unlock();
  if (!is_sync) {
    err = std::make_error_code(std::errc::timed_out);
    return;
  }
  
  // if code_ is still empty, it means the message received bad the server was
  // baddly formatted
  if (code_.empty()) {
    err = std::make_error_code(std::errc::bad_message);
    return;
  }
}
  
void Client::QueryAccessToken(std::string* p_token_type,
                              std::string* p_access_token,
                              std::error_code &err) {
  web::json::value access_token_json;
  web::http::client::http_client auth_client(
      "https://accounts.spotify.com/api/token");
    
  std::string request_data;
  // If we haven't got any refresh token, it means it the first query. We do an
  // authorization_code
  // else it means it's not the first query. We can do a refresh_token
  if (refresh_token_.empty()) {
    request_data= "grant_type=authorization_code&code=" + code_
                  + "&redirect_uri=http://localhost:"
                  + std::to_string(redirect_uri_port_)
                  + "&client_id=" + client_id_
                  + "&client_secret=" + client_secret_;
  } else {
    request_data= "grant_type=refresh_token&refresh_token=" + refresh_token_
                  + "&client_id=" + client_id_
                  + "&client_secret=" + client_secret_;
  }
  
  auth_client.request(web::http::methods::POST,
                      "",
                      request_data,
                      "application/x-www-form-urlencoded")
  
  .then([](web::http::http_response response){
    return response.extract_json();
  })
  
  .then([&access_token_json](web::json::value json_value) {
    access_token_json = json_value;
  })
  
  .wait();
  
  // Get refresh token if any
  if (access_token_json.has_field("refresh_token") &&
      access_token_json["refresh_token"].is_string()) {
    refresh_token_ = access_token_json["refresh_token"].serialize();
    // serialize add a \" char at the begining and end
    RemoveFirstAndLastCharacters(&refresh_token_, '\"');
  }
  
  if (access_token_json.has_field("token_type") &&
      access_token_json.has_field("access_token") &&
      access_token_json["token_type"].is_string() &&
      access_token_json["access_token"].is_string()) {
    *p_token_type = access_token_json["token_type"].serialize();
    *p_access_token = access_token_json["access_token"].serialize();
    // serialize add a \" char at the begining and end
    RemoveFirstAndLastCharacters(p_token_type, '\"');
    RemoveFirstAndLastCharacters(p_access_token, '\"');
  } else {
    err = std::make_error_code(std::errc::bad_message);
  }
}
  
std::shared_ptr<SearchEngineInterface> Client::GetSearchEngine() {
  return std::make_shared<spotify::SearchEngine>(shared_from_this());
}
  
}  // namespace spotify
}  // namespace lizz
