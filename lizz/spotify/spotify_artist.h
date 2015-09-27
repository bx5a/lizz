#ifndef LIZZ_SPOTIFY_SPOTIFY_ARTIST_H_
#define LIZZ_SPOTIFY_SPOTIFY_ARTIST_H_

#include <system_error>
#include <memory>

#include <boost/property_tree/ptree.hpp>

#include "interfaces/artist.h"

namespace lizz {
  
class SpotifyObject;
class SpotifyArtist : public Artist {
 public:
  static constexpr const char* kTypeName = "artist";
  static constexpr const char* kPathInJson = "artists.items";
      
  SpotifyArtist(const boost::property_tree::ptree& artist_info);
  SpotifyArtist(std::shared_ptr<SpotifyObject> p_obj);
  
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
  std::shared_ptr<SpotifyObject> p_object_;
};
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_SPOTIFY_ARTIST_H_
