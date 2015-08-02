#ifndef LIZZ_COMMON_SEARCH_RESULT_H_
#define LIZZ_COMMON_SEARCH_RESULT_H_

#include <list>
#include "track_interface.h"
#include "album_interface.h"
#include "artist_interface.h"
#include "playlist_interface.h"

namespace lizz {
  
class SearchResult {
 public:
  void Add(std::shared_ptr<TrackInterface> ptr);
  void Add(std::shared_ptr<AlbumInterface> ptr);
  void Add(std::shared_ptr<ArtistInterface> ptr);
  void Add(std::shared_ptr<PlaylistInterface> ptr);
  
  // TODO(bx5a): give a Get() templatized function
  const std::list<std::shared_ptr<TrackInterface>>&& GetTracks() const;
  const std::list<std::shared_ptr<AlbumInterface>>&& GetAlbums() const;
  const std::list<std::shared_ptr<ArtistInterface>>&& GetArtists() const;
  const std::list<std::shared_ptr<PlaylistInterface>>&& GetPlaylists() const;
  
private:
  std::list<std::shared_ptr<TrackInterface>> track_list_;
  std::list<std::shared_ptr<AlbumInterface>> album_list_;
  std::list<std::shared_ptr<ArtistInterface>> artist_list_;
  std::list<std::shared_ptr<PlaylistInterface>> playlist_list_;
};
  
}  // namespace lizz

#endif  // LIZZ_COMMON_SEARCH_RESULT_H_
