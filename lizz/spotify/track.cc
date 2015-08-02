#include "spotify/track.h"


namespace lizz {
namespace spotify {

Track::Track(const boost::property_tree::ptree& track_info)
  : track_info_(track_info) {}

//std::shared_ptr<AlbumInterface> Track::GetAlbum(std::error_code& err) const {
//  return std::make_shared<AlbumInterface>(nullptr);
//}
//std::list<std::shared_ptr<ArtistInterface>>
//    Track::GetArtists(std::error_code& err) const {
//    return std::list<std::shared_ptr<ArtistInterface>>();
//}
std::list<std::string> Track::GetAvailableMarkets(std::error_code& err) const {
  
}
int Track::GetDiscNumber(std::error_code& err) const {
  
}
std::chrono::milliseconds Track::GetDuration(std::error_code& err) const {
  
}
bool Track::GetExplicit(std::error_code& err) const {
  
}
std::string Track::GetHref(std::error_code& err) const {
  
}
std::string Track::GetId(std::error_code& err) const {
  
}
bool Track::GetIsPlayable(std::error_code& err) const {
  
}
std::string Track::GetName(std::error_code& err) const {
  
}
uint8_t Track::GetPopularity(std::error_code& err) const {
  
}
uint16_t Track::GetTrackNumber(std::error_code& err) const {
  
}
std::string Track::GetUri(std::error_code& err) const {
  
}

}  // namespace spotify
}  // namespace lizz
