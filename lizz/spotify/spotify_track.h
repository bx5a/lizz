#ifndef LIZZ_SPOTIFY_SPOTIFY_TRACK_H_
#define LIZZ_SPOTIFY_SPOTIFY_TRACK_H_

#include <boost/property_tree/ptree.hpp>

#include "interfaces/track.h"

// Interface obtained from
// https://developer.spotify.com/web-api/object-model/
namespace lizz {
class Album;
class Artist;
class SpotifyObject;
class SpotifyTrack : public Track {
 public:
  static constexpr const char* kTypeName = "track";
  static constexpr const char* kPathInJson = "tracks.items";
  
  SpotifyTrack(const boost::property_tree::ptree& track_info);
  SpotifyTrack(std::shared_ptr<SpotifyObject> p_obj);
  
  std::shared_ptr<Album> GetAlbum(std::error_code& err) const;
  std::list<std::shared_ptr<Artist>>
      GetArtists(std::error_code& err) const;
  std::list<std::string> GetAvailableMarkets(std::error_code& err) const;
  uint8_t GetDiscNumber(std::error_code& err) const;
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
  std::shared_ptr<SpotifyObject> p_object_;
};
}  // namespace lizz

#endif  // LIZZ_SPOTIFY_SPOTIFY_TRACK_H_
