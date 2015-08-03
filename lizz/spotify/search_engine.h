#ifndef LIZZ_SPOTIFY_SEARCH_ENGINE_H_
#define LIZZ_SPOTIFY_SEARCH_ENGINE_H_

#include <memory>
#include <list>

#include <cpprest/http_client.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "search_engine_interface.h"

namespace lizz {
namespace spotify {
class Client;
class SearchEngine : public SearchEngineInterface {
 public:
  SearchEngine(std::shared_ptr<Client> p_spotify_client);
  Future<SearchResult> Run(const std::string& query,
                           uint16_t track_number,
                           uint16_t album_number,
                           uint16_t artist_number,
                           uint16_t playlist_number);
  
 private:
  SearchResult PrivateRun(const std::string& query,
                          uint16_t track_number,
                          uint16_t album_number,
                          uint16_t artist_number,
                          uint16_t playlist_number,
                          std::error_code& err);
  
  template <class T>
  std::list<std::shared_ptr<T>> Search(const std::string& query,
                                       uint16_t entry_number,
                                       const std::string& token_type,
                                       const std::string& token,
                                       std::error_code& err) {
    auto request = MakeRequest(query, T::kTypeName, entry_number,
                               token_type, token);
    std::list<std::shared_ptr<T>> res;
    rest_client_.request(request)
    .then([](web::http::http_response response){
      return response.extract_string();
    })
    .then([this, &err, &res](utility::string_t response) {
      ParseResponse(response, T::kPathInJson, &res, err);
    })
    .wait();
    
    return res;
  }
  
  web::http::http_request MakeRequest(const std::string& query,
                                      const std::string& entry_type,
                                      uint16_t entry_number,
                                      const std::string& token_type,
                                      const std::string& token) const;
          
  template <class T>
  void ParseResponse(const std::string& response,
                     const std::string& array_name,
                     std::list<std::shared_ptr<T>>* p_res,
                     std::error_code& err) {
    boost::property_tree::ptree tree;
    try {
      std::stringstream ss;
      ss << response;
      boost::property_tree::read_json(ss, tree);
    } catch(...) {
      err = std::make_error_code(std::errc::bad_message);
      return;
    }
    auto first_item = tree.get_child_optional(array_name);
    
    if (!first_item) {
      // TODO(bx5a): handle error from json
      err = std::make_error_code(std::errc::bad_message);
      return;
    }
    
    for (const auto& track : tree.get_child(array_name)) {
      p_res->push_back(std::make_shared<T>(track.second));
    }
  }
  
  std::shared_ptr<Client> p_client_;
  web::http::client::http_client rest_client_;
};
  
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_SEARCH_ENGINE_H_