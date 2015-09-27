#ifndef LIZZ_SPOTIFY_SPOTIFY_SEARCH_ENGINE_H_
#define LIZZ_SPOTIFY_SPOTIFY_SEARCH_ENGINE_H_

#include <memory>
#include <list>

#include <cpprest/http_client.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "interfaces/search_engine.h"

namespace lizz {
class SpotifyClient;
class SpotifySearchEngine : public SearchEngine {
 public:
  SpotifySearchEngine(std::shared_ptr<SpotifyClient> p_spotify_client);
  // TODO(bxa): rename to Query ?
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
  
  // TODO(bxa): Move private member to .cc file
  
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
  
  std::shared_ptr<SpotifyClient> p_client_;
  web::http::client::http_client rest_client_;
};
  
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_SPOTIFY_SEARCH_ENGINE_H_