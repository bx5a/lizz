#ifndef LIZZ_SPOTIFY_SPOTIFY_ALBUM_H_
#define LIZZ_SPOTIFY_SPOTIFY_ALBUM_H_

#include <memory>

#include <boost/property_tree/ptree_fwd.hpp>

#include "interfaces/fwd.h"
#include "interfaces/album.h"

namespace lizz {
namespace spotify {
class SpotifyObject;
  
class SpotifyAlbum : public Album {
 public:
  static constexpr const char* kTypeName = "album";
  static constexpr const char* kPathInJson = "albums.items";
  
  SpotifyAlbum(const boost::property_tree::ptree& album_info);
  SpotifyAlbum(std::shared_ptr<SpotifyObject> p_obj);
  
  std::string GetAlbumType(std::error_code& err) const;
  ArtistList GetArtists(std::error_code& err) const;
  std::list<std::string> GetAvailableMarkets(std::error_code& err) const;
  // GetCopyrights
  // GetExternalIds
  // GetExternalUrls
  std::list<std::string> GetGenres(std::error_code& err) const;
  std::string GetHref(std::error_code& err) const;
  std::string GetId(std::error_code& err) const;
  // GetImages
  std::string GetName(std::error_code& err) const;
  uint8_t GetPopularity(std::error_code& err) const;
  // TOOD(bx5a): should be a unique function for release date and return chrono
  std::string GetReleaseDate(std::error_code& err) const;
  std::string GetReleaseDatePrecision(std::error_code& err) const;
  TrackList GetTracks(std::error_code& err) const;
  std::string GetType(std::error_code& err) const;
  std::string GetUri(std::error_code& err) const;
  
 private:
  std::shared_ptr<SpotifyObject> p_object_;
};
  
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_SPOTIFY_ALBUM_H_
