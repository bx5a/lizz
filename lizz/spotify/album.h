#ifndef LIZZ_SPOTIFY_ALBUM_H_
#define LIZZ_SPOTIFY_ALBUM_H_

#include <boost/property_tree/ptree.hpp>

namespace lizz {
namespace spotify {
class Album : public AlbumInterface {
 public:
  static constexpr const char* kTypeName = "album";
  static constexpr const char* kPathInJson = "albums.items";
  
  Album(const boost::property_tree::ptree& album_info) {}
};
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_ALBUM_H_
