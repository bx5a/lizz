#ifndef LIZZ_SPOTIFY_SEARCH_ENGINE_H_
#define LIZZ_SPOTIFY_SEARCH_ENGINE_H_

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
  
  std::shared_ptr<Client> p_client_;
};
  
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_SEARCH_ENGINE_H_