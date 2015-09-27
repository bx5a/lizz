#include "spotify/spotify_object.h"
#include "spotify/spotify_track.h"
#include "spotify/spotify_album.h"
#include "spotify/spotify_artist.h"

#include "interfaces/album.h"
#include "interfaces/artist.h"

namespace lizz {
  
SpotifyTrack::SpotifyTrack(const boost::property_tree::ptree& track_info)
    : p_object_(std::make_shared<SpotifyObject>()) {
  p_object_->Init(track_info);
}
  
SpotifyTrack::SpotifyTrack(std::shared_ptr<SpotifyObject> p_obj) : p_object_(p_obj) {}

std::shared_ptr<Album> SpotifyTrack::GetAlbum(std::error_code& err) const {
  p_object_->GetObject("album", err);
  return std::make_shared<SpotifyAlbum>(p_object_);
}
  
std::list<std::shared_ptr<Artist>>
    SpotifyTrack::GetArtists(std::error_code& err) const {
  std::list<std::shared_ptr<Artist>> ret;
  auto artists = p_object_->GetObjectList("artists", err);
  for (const auto& artist: artists) {
    ret.push_back(std::make_shared<SpotifyArtist>(artist));
  }
  return ret;
}
  
std::list<std::string> SpotifyTrack::GetAvailableMarkets(std::error_code& err) const {
  return p_object_->GetStringList("available_markets", err);
}
  
uint8_t SpotifyTrack::GetDiscNumber(std::error_code& err) const {
  return p_object_->GetUInt8("disc_number", err);
}
  
std::chrono::milliseconds SpotifyTrack::GetDuration(std::error_code& err) const {
  auto res = p_object_->GetUInt8("duration_ms", err);
  if (err) {
    return std::chrono::milliseconds(0);
  }
  return std::chrono::milliseconds(res);
}
  
bool SpotifyTrack::GetExplicit(std::error_code& err) const {
  return p_object_->GetBool("explicit", err);
}
  
std::string SpotifyTrack::GetHref(std::error_code& err) const {
  return p_object_->GetString("href", err);
}
  
std::string SpotifyTrack::GetId(std::error_code& err) const {
  return p_object_->GetString("id", err);
}
  
std::string SpotifyTrack::GetName(std::error_code& err) const {
  return p_object_->GetString("name", err);
}
  
uint8_t SpotifyTrack::GetPopularity(std::error_code& err) const {
  return p_object_->GetUInt8("popularity", err);
}
  
uint16_t SpotifyTrack::GetTrackNumber(std::error_code& err) const {
  return p_object_->GetUInt16("track_number", err);
}
  
std::string SpotifyTrack::GetUri(std::error_code& err) const {
  return p_object_->GetString("uri", err);
}

}  // namespace lizz
