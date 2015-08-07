#include "spotify/object.h"
#include "spotify/artist.h"

#include "common/utils/property_tree.h"

namespace lizz {
namespace spotify {

Artist::Artist(const boost::property_tree::ptree& artist_info) :
    p_object_(std::make_shared<Object>()) {
  p_object_->Init(artist_info);
}
  
Artist::Artist(std::shared_ptr<Object> p_obj) : p_object_(p_obj) {}
  
// GetExternalUrls
// GetFollowers
std::list<std::string> Artist::GetGenres(std::error_code& err) const {
  return p_object_->GetStringList("genres", err);
}
std::string Artist::GetHref(std::error_code& err) const {
  return p_object_->GetString("href", err);
}
std::string Artist::GetId(std::error_code& err) const {
  return p_object_->GetString("id", err);
}
// GetImages
std::string Artist::GetName(std::error_code& err) const {
  return p_object_->GetString("name", err);
}
uint8_t Artist::GetPopularity(std::error_code& err) const {
  return p_object_->GetUInt8("popularity", err);
}
std::string Artist::GetType(std::error_code& err) const {
  return p_object_->GetString("type", err);
}
std::string Artist::GetUri(std::error_code& err) const {
  return p_object_->GetString("uri", err);
}

}  // namespace spotify
}  // namespace lizz
