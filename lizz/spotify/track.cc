#include "spotify/track.h"
#include "spotify/album.h"
#include "spotify/artist.h"

#include "interfaces/album_interface.h"
#include "interfaces/artist_interface.h"

#include "common/utils/property_tree.h"

namespace lizz {
namespace spotify {
  
Track::Track(const boost::property_tree::ptree& track_info)
  : track_info_(track_info) {}

std::shared_ptr<AlbumInterface> Track::GetAlbum(std::error_code& err) const {
  auto album_json = track_info_.get_child_optional("album");
  if (!album_json) {
    err = std::make_error_code(std::errc::invalid_seek);
    return std::shared_ptr<AlbumInterface>(nullptr);
  }
  return std::make_shared<Album>(album_json.get());
}
  
std::list<std::shared_ptr<ArtistInterface>>
    Track::GetArtists(std::error_code& err) const {
  std::list<std::shared_ptr<ArtistInterface>> ret;
  auto to_run = [&ret](const boost::property_tree::ptree& tree){
    ret.push_back(std::make_shared<Artist>(tree));
  };
  RunOnChilds(track_info_, "artists", to_run, err);
  return ret;
}
  
std::list<std::string> Track::GetAvailableMarkets(std::error_code& err) const {
  return GetListFromTree<std::string>(track_info_, "available_markets", err);
}
  
int Track::GetDiscNumber(std::error_code& err) const {
  return GetFromTree<int>(track_info_, "disc_number", err);
}
  
std::chrono::milliseconds Track::GetDuration(std::error_code& err) const {
  auto res = GetFromTree<int>(track_info_, "duration_ms", err);
  if (err) {
    return std::chrono::milliseconds(0);
  }
  return std::chrono::milliseconds(res);
}
  
bool Track::GetExplicit(std::error_code& err) const {
  return GetFromTree<bool>(track_info_, "explicit", err);
}
  
std::string Track::GetHref(std::error_code& err) const {
  return GetFromTree<std::string>(track_info_, "href", err);
}
  
std::string Track::GetId(std::error_code& err) const {
  return GetFromTree<std::string>(track_info_, "id", err);
}
  
std::string Track::GetName(std::error_code& err) const {
  return GetFromTree<std::string>(track_info_, "name", err);
}
  
uint8_t Track::GetPopularity(std::error_code& err) const {
  return GetFromTree<uint8_t>(track_info_, "popularity", err);
}
  
uint16_t Track::GetTrackNumber(std::error_code& err) const {
  return GetFromTree<uint16_t>(track_info_, "track_number", err);
}
  
std::string Track::GetUri(std::error_code& err) const {
  return GetFromTree<std::string>(track_info_, "uri", err);
}

}  // namespace spotify
}  // namespace lizz
