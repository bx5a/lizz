#include "spotify/search_engine.h"

#include <cpprest/http_client.h>

#include "common/log.h"
#include "common/future/utils.h"

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
  
  return SearchResult();
}
    
}  // namespace spotify
}  // namespace lizz
