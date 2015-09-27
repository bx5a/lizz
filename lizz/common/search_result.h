#ifndef LIZZ_COMMON_SEARCH_RESULT_H_
#define LIZZ_COMMON_SEARCH_RESULT_H_

#include <list>

namespace lizz {
class Track;
class Album;
class Artist;
class Playlist;
class SearchResult {
 public:
  void Add(std::shared_ptr<Track> ptr);
  void Add(std::shared_ptr<Album> ptr);
  void Add(std::shared_ptr<Artist> ptr);
  void Add(std::shared_ptr<Playlist> ptr);
  
  // TODO(bx5a): give a Get() templatized function
  const std::list<std::shared_ptr<Track>>&& GetTracks() const;
  const std::list<std::shared_ptr<Album>>&& GetAlbums() const;
  const std::list<std::shared_ptr<Artist>>&& GetArtists() const;
  const std::list<std::shared_ptr<Playlist>>&& GetPlaylists() const;
  
private:
  std::list<std::shared_ptr<Track>> track_list_;
  std::list<std::shared_ptr<Album>> album_list_;
  std::list<std::shared_ptr<Artist>> artist_list_;
  std::list<std::shared_ptr<Playlist>> playlist_list_;
};
  
}  // namespace lizz

#endif  // LIZZ_COMMON_SEARCH_RESULT_H_
