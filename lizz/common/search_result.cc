#include "common/search_result.h"

#include "interfaces/track.h"
#include "interfaces/album.h"
#include "interfaces/artist.h"
#include "interfaces/playlist.h"

namespace lizz {
  
void SearchResult::Add(std::shared_ptr<Track> ptr) {
  track_list_.push_back(ptr);
}
void SearchResult::Add(std::shared_ptr<Album> ptr) {
  album_list_.push_back(ptr);
}
void SearchResult::Add(std::shared_ptr<Artist> ptr) {
  artist_list_.push_back(ptr);
}
void SearchResult::Add(std::shared_ptr<Playlist> ptr) {
  playlist_list_.push_back(ptr);
}
    
// TODO(bx5a): give a Get() templatized function
const std::list<std::shared_ptr<Track>>&&
    SearchResult::GetTracks() const {
  return std::move(track_list_);
}
const std::list<std::shared_ptr<Album>>&&
    SearchResult::GetAlbums() const {
  return std::move(album_list_);
}
const std::list<std::shared_ptr<Artist>>&&
    SearchResult::GetArtists() const {
  return std::move(artist_list_);
}
const std::list<std::shared_ptr<Playlist>>&&
    SearchResult::GetPlaylists() const {
  return std::move(playlist_list_);
}
  
}  // namespace lizz
