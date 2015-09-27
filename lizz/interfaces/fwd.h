#ifndef LIZZ_INTERFACES_FWD_H_
#define LIZZ_INTERFACES_FWD_H_

#include <memory>
#include <list>

namespace lizz {
class Album;
class Artist;
class Client;
class Playlist;
class SearchEngine;
class Track;
  
using AlbumPtr = std::shared_ptr<Album>;
using ArtistPtr = std::shared_ptr<Artist>;
using ClientPtr = std::shared_ptr<Client>;
using PlaylistPtr = std::shared_ptr<Playlist>;
using SearchEnginePtr = std::shared_ptr<SearchEngine>;
using TrackPtr = std::shared_ptr<Track>;
  
using AlbumList = std::list<AlbumPtr>;
using ArtistList = std::list<ArtistPtr>;
using PlaylistList = std::list<PlaylistPtr>;
using TrackList = std::list<TrackPtr>;
}  // namespace lizz

#endif  // LIZZ_INTERFACES_FWD_H_
