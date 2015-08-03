#include "spotify/search_engine.h"

#include "common/utils/log.h"
#include "common/future/utils.h"

#include "spotify/client.h"
#include "spotify/track.h"
#include "spotify/album.h"
#include "spotify/artist.h"
#include "spotify/playlist.h"

namespace lizz {
namespace spotify {
  
SearchEngine::SearchEngine(std::shared_ptr<Client> p_spotify_client) :
    p_client_(p_spotify_client),
    rest_client_("https://api.spotify.com")
  {}

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
    return PrivateRun(query,
                      track_number,
                      album_number,
                      artist_number,
                      playlist_number,
                      err);
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
  SearchResult sr;
  if (track_number > 0) {
    auto tracks = Search<Track>(query, track_number, type, token, err);
    for (const auto& track: tracks) {
      sr.Add(track);
    }
  }
  if (album_number > 0) {
    auto albums = Search<Album>(query, album_number, type, token, err);
    for (const auto& album : albums) {
      sr.Add(album);
    }
  }
  if (artist_number > 0) {
    auto artists = Search<Artist>(query, artist_number, type, token, err);
    for (const auto& artist : artists) {
      sr.Add(artist);
    }
  }
  if (playlist_number > 0) {
    auto playlists = Search<Playlist>(query, playlist_number, type, token, err);
    for (const auto& playlist : playlists) {
      sr.Add(playlist);
    }
  }
  return sr;
}
  
web::http::http_request SearchEngine::MakeRequest(
    const std::string& query, const std::string& entry_type,
    uint16_t entry_number, const std::string& token_type,
    const std::string& token) const {
  web::http::http_request request(web::http::methods::GET);
  request.headers().add("Authorization", token_type + " " + token);
  web::http::uri_builder search_uri("/v1/search");
  search_uri.append_query("q", query);
  search_uri.append_query("limit", entry_number);
  search_uri.append_query("type", entry_type);
  request.set_request_uri(search_uri.to_uri());
  return request;
}
  
}  // namespace spotify
}  // namespace lizz
