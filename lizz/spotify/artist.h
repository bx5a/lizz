#ifndef LIZZ_SPOTIFY_ARTIST_H_
#define LIZZ_SPOTIFY_ARTIST_H_

#include <boost/property_tree/ptree.hpp>

namespace lizz {
namespace spotify {
class Artist : public ArtistInterface {
 public:
  static constexpr const char* kTypeName = "artist";
  static constexpr const char* kPathInJson = "artists.items";
      
  Artist(const boost::property_tree::ptree& artist_info) {}
};
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_ARTIST_H_
