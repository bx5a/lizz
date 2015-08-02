#ifndef LIZZ_SPOTIFY_TRACK_H_
#define LIZZ_SPOTIFY_TRACK_H_

#include <system_error>
#include <list>
#include <memory>
#include <chrono>

#include <boost/property_tree/ptree.hpp>

#include "track_interface.h"
#include "album_interface.h"
#include "artist_interface.h"

// Interface obtained from
// https://developer.spotify.com/web-api/object-model/
namespace lizz {
namespace spotify {
class Track : public TrackInterface {
 public:
  static constexpr const char* kTypeName = "track";
  static constexpr const char* kPathInJson = "tracks.items";
  
  Track(const boost::property_tree::ptree& track_info);
  
//  std::shared_ptr<AlbumInterface> GetAlbum(std::error_code& err) const;
//  std::list<std::shared_ptr<ArtistInterface>>
//      GetArtists(std::error_code& err) const;
  std::list<std::string> GetAvailableMarkets(std::error_code& err) const;
  int GetDiscNumber(std::error_code& err) const;
  std::chrono::milliseconds GetDuration(std::error_code& err) const;
  bool GetExplicit(std::error_code& err) const;
  // GetExternalIds
  // GetExternalUrls
  std::string GetHref(std::error_code& err) const;
  std::string GetId(std::error_code& err) const;
  // GetIsPlayable
  // GetIsLinkedFrom
  std::string GetName(std::error_code& err) const;
  uint8_t GetPopularity(std::error_code& err) const;
  // GetPreviewUrl
  uint16_t GetTrackNumber(std::error_code& err) const;
  std::string GetUri(std::error_code& err) const;

private:
  template <typename T>
  T Get(const std::string& key, std::error_code& err) const {
    auto res = track_info_.get_optional<T>(key);
    if (!res) {
      err = std::make_error_code(std::errc::invalid_seek);
    }
    return res.get();
  }
  
  boost::property_tree::ptree track_info_;
};
}  // namespace spotify
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_TRACK_H_
