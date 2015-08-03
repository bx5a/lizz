#include "common/search_result.h"

#include "interfaces/track_interface.h"
#include "interfaces/album_interface.h"
#include "interfaces/artist_interface.h"
#include "interfaces/playlist_interface.h"

namespace lizz {
  
void SearchResult::Add(std::shared_ptr<TrackInterface> ptr) {
  track_list_.push_back(ptr);
}
void SearchResult::Add(std::shared_ptr<AlbumInterface> ptr) {
  album_list_.push_back(ptr);
}
void SearchResult::Add(std::shared_ptr<ArtistInterface> ptr) {
  artist_list_.push_back(ptr);
}
void SearchResult::Add(std::shared_ptr<PlaylistInterface> ptr) {
  playlist_list_.push_back(ptr);
}
    
// TODO(bx5a): give a Get() templatized function
const std::list<std::shared_ptr<TrackInterface>>&&
    SearchResult::GetTracks() const {
  return std::move(track_list_);
}
const std::list<std::shared_ptr<AlbumInterface>>&&
    SearchResult::GetAlbums() const {
  return std::move(album_list_);
}
const std::list<std::shared_ptr<ArtistInterface>>&&
    SearchResult::GetArtists() const {
  return std::move(artist_list_);
}
const std::list<std::shared_ptr<PlaylistInterface>>&&
    SearchResult::GetPlaylists() const {
  return std::move(playlist_list_);
}
  
}  // namespace lizz
