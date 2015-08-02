#include "spotify/search_engine.h"

#include <cpprest/http_client.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "common/log.h"
#include "common/future/utils.h"
#include "spotify/client.h"
#include "spotify/track.h"

namespace lizz {
namespace spotify {
  
SearchEngine::SearchEngine(std::shared_ptr<Client> p_spotify_client) :
    p_client_(p_spotify_client) {}

Future<SearchResult> SearchEngine::Run(const std::string& query,
                                       uint16_t track_number,
                                       uint16_t album_number,
                                       uint16_t artist_number,
                                       uint16_t playlist_number) {
  auto fn = [this,
             &query,
             track_number,
             album_number,
             artist_number,
             playlist_number](std::error_code& err) {
    auto result = PrivateRun(query,
                             track_number,
                             album_number,
                             artist_number,
                             playlist_number,
                             err);
    if (err) {
      LOG(debug) << "Search failed: " << err.value();
    }
    return result;
  };
  
  return make_std_future<SearchResult>(fn);
}
  
SearchResult SearchEngine::PrivateRun(const std::string& query,
                                      uint16_t track_number,
                                      uint16_t album_number,
                                      uint16_t artist_number,
                                      uint16_t playlist_number,
                                      std::error_code& err) {
  std::string type, token;
  p_client_->QueryAccessToken(&type, &token, err);
  if (err) {
    return SearchResult();
  }
  auto tracks = SearchTracks(query, track_number, type, token, err);
  SearchResult sr;
  for (const auto& track: tracks) {
    sr.Add(track);
  }
  return sr;
}
  
std::list<std::shared_ptr<TrackInterface>>
  SearchEngine::SearchTracks(const std::string& query,
                             uint16_t track_number,
                             const std::string& token_type,
                             const std::string& token,
                             std::error_code& err) {
    
  web::http::client::http_client spotify_client("https://api.spotify.com");
    
  web::http::http_request request(web::http::methods::GET);
  request.headers().add("Authorization", token_type + " " + token);
  web::http::uri_builder search_uri("/v1/search");
  search_uri.append_query("q", query);
  search_uri.append_query("limit", track_number);
  search_uri.append_query("type", "track");
    
  request.set_request_uri(search_uri.to_uri());
    
  std::list<std::shared_ptr<TrackInterface>> res;
    
  spotify_client.request(request)
  .then([](web::http::http_response response){
    return response.extract_string();
  })
    
  .then([&err, &res](utility::string_t response) {
    std::cout<<response<<std::endl;
    
    boost::property_tree::ptree tree;
    try {
      std::stringstream ss;
      ss << response;
      boost::property_tree::read_json(ss, tree);
    } catch(...) {
      err = std::make_error_code(std::errc::bad_message);
      return;
    }
    auto first_item = tree.get_child_optional("tracks.items");
    
    if (!first_item) {
      // TODO(bx5a): handle error from json
      err = std::make_error_code(std::errc::bad_message);
      return;
    }
    
    for (const auto& track : tree.get_child("tracks.items")) {
      res.push_back(std::make_shared<Track>(track.second));
    }
  })
  .wait();
    
  return res;
}
    
}  // namespace spotify
}  // namespace lizz
