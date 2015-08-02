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
  std::list<std::string> res;
  auto available_markets = track_info_.get_child_optional("available_markets");
  if (!available_markets) {
    err = std::make_error_code(std::errc::invalid_seek);
    return res;
  }
  for (const auto& market : track_info_.get_child("available_markets")) {
    auto val = market.second.get_optional<std::string>("");
    if (val) {
      res.push_back(val.get());
    }
  }
  return res;
}
int Track::GetDiscNumber(std::error_code& err) const {
  return Get<int>("disc_number", err);
}
std::chrono::milliseconds Track::GetDuration(std::error_code& err) const {
  auto res = Get<int>("duration_ms", err);
  if (err) {
    return std::chrono::milliseconds(0);
  }
  return std::chrono::milliseconds(res);
}
bool Track::GetExplicit(std::error_code& err) const {
  return Get<bool>("explicit", err);
}
std::string Track::GetHref(std::error_code& err) const {
  return Get<std::string>("href", err);
}
std::string Track::GetId(std::error_code& err) const {
  return Get<std::string>("id", err);
}
std::string Track::GetName(std::error_code& err) const {
  return Get<std::string>("name", err);
}
uint8_t Track::GetPopularity(std::error_code& err) const {
  return Get<uint8_t>("popularity", err);
}
uint16_t Track::GetTrackNumber(std::error_code& err) const {
  return Get<uint16_t>("track_number", err);
}
std::string Track::GetUri(std::error_code& err) const {
  return Get<std::string>("uri", err);
}

}  // namespace spotify
}  // namespace lizz
