#ifndef LIZZ_SPOTIFY_SEARCH_ENGINE_H_
#define LIZZ_SPOTIFY_SEARCH_ENGINE_H_

#include <memory>
#include <list>

#include "search_engine_interface.h"

namespace lizz {
class TrackInterface;
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
  
  std::list<std::shared_ptr<TrackInterface>>
    SearchTracks(const std::string& query,
                 uint16_t track_number,
                 const std::string& token_type,
                 const std::string& token,
                 std::error_code& err);
  
  std::shared_ptr<Client> p_client_;
};
  
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_SEARCH_ENGINE_H_