#ifndef LIZZ_SPOTIFY_PLAYLIST_H_
#define LIZZ_SPOTIFY_PLAYLIST_H_

#include <boost/property_tree/ptree.hpp>

namespace lizz {
namespace spotify {
class Playlist : public PlaylistInterface {
 public:
  static constexpr const char* kTypeName = "playlist";
  static constexpr const char* kPathInJson = "playlists.items";
  
  Playlist(const boost::property_tree::ptree& playlist_info) {}
};
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_PLAYLIST_H_
