#ifndef LIZZ_SPOTIFY_ARTIST_H_
#define LIZZ_SPOTIFY_ARTIST_H_

#include <string>
#include <list>
#include <system_error>

#include <boost/property_tree/ptree.hpp>

#include "interfaces/artist_interface.h"

namespace lizz {
namespace spotify {
class Object;
class Artist : public ArtistInterface {
 public:
  static constexpr const char* kTypeName = "artist";
  static constexpr const char* kPathInJson = "artists.items";
      
  Artist(const boost::property_tree::ptree& artist_info);
  Artist(std::shared_ptr<Object> p_obj);
  
  // GetExternalUrls
  // GetFollowers
  std::list<std::string> GetGenres(std::error_code& err) const;
  std::string GetHref(std::error_code& err) const;
  std::string GetId(std::error_code& err) const;
  // GetImages
  std::string GetName(std::error_code& err) const;
  uint8_t GetPopularity(std::error_code& err) const;
  std::string GetType(std::error_code& err) const;
  std::string GetUri(std::error_code& err) const;

 private:
  std::shared_ptr<Object> p_object_;
};
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_ARTIST_H_
