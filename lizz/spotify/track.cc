#include "spotify/object.h"
#include "spotify/track.h"
#include "spotify/album.h"
#include "spotify/artist.h"

#include "interfaces/album_interface.h"
#include "interfaces/artist_interface.h"

namespace lizz {
namespace spotify {
  
Track::Track(const boost::property_tree::ptree& track_info)
    : p_object_(std::make_shared<Object>()) {
  p_object_->Init(track_info);
}
  
Track::Track(std::shared_ptr<Object> p_obj) : p_object_(p_obj) {}

std::shared_ptr<AlbumInterface> Track::GetAlbum(std::error_code& err) const {
  p_object_->GetObject("album", err);
  return std::make_shared<Album>(p_object_);
}
  
std::list<std::shared_ptr<ArtistInterface>>
    Track::GetArtists(std::error_code& err) const {
  std::list<std::shared_ptr<ArtistInterface>> ret;
  auto artists = p_object_->GetObjectList("artists", err);
  for (const auto& artist: artists) {
    ret.push_back(std::make_shared<Artist>(artist));
  }
  return ret;
}
  
std::list<std::string> Track::GetAvailableMarkets(std::error_code& err) const {
  return p_object_->GetStringList("available_markets", err);
}
  
uint8_t Track::GetDiscNumber(std::error_code& err) const {
  return p_object_->GetUInt8("disc_number", err);
}
  
std::chrono::milliseconds Track::GetDuration(std::error_code& err) const {
  auto res = p_object_->GetUInt8("duration_ms", err);
  if (err) {
    return std::chrono::milliseconds(0);
  }
  return std::chrono::milliseconds(res);
}
  
bool Track::GetExplicit(std::error_code& err) const {
  return p_object_->GetBool("explicit", err);
}
  
std::string Track::GetHref(std::error_code& err) const {
  return p_object_->GetString("href", err);
}
  
std::string Track::GetId(std::error_code& err) const {
  return p_object_->GetString("id", err);
}
  
std::string Track::GetName(std::error_code& err) const {
  return p_object_->GetString("name", err);
}
  
uint8_t Track::GetPopularity(std::error_code& err) const {
  return p_object_->GetUInt8("popularity", err);
}
  
uint16_t Track::GetTrackNumber(std::error_code& err) const {
  return p_object_->GetUInt16("track_number", err);
}
  
std::string Track::GetUri(std::error_code& err) const {
  return p_object_->GetString("uri", err);
}

}  // namespace spotify
}  // namespace lizz
