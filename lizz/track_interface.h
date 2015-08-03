#ifndef LIZZ_TRACK_INTERFACE_H_
#define LIZZ_TRACK_INTERFACE_H_

#include <string>
#include <system_error>
#include <memory>
#include <chrono>
#include <list>

namespace lizz {
class AlbumInterface;
class ArtistInterface;

class TrackInterface {
 public:
  virtual std::shared_ptr<AlbumInterface>
      GetAlbum(std::error_code& err) const = 0;
  virtual std::list<std::shared_ptr<ArtistInterface>>
      GetArtists(std::error_code& err) const = 0;
  virtual std::string GetName(std::error_code& err) const = 0;
  virtual std::chrono::milliseconds GetDuration(std::error_code& err) const = 0;
  virtual uint16_t GetTrackNumber(std::error_code& err) const = 0;
};
  
}  // namespace lizz

#endif  // LIZZ_TRACK_INTERFACE_H_
