#ifndef LIZZ_TRACK_H_
#define LIZZ_TRACK_H_

#include <string>
#include <system_error>
#include <memory>
#include <chrono>
#include <list>

#include "interfaces/fwd.h"

namespace lizz {
class Album;
class Artist;

class Track {
 public:
  virtual AlbumPtr GetAlbum(std::error_code& err) const = 0;
  virtual ArtistList GetArtists(std::error_code& err) const = 0;
  virtual std::string GetName(std::error_code& err) const = 0;
  virtual std::chrono::milliseconds GetDuration(std::error_code& err) const = 0;
  virtual uint16_t GetTrackNumber(std::error_code& err) const = 0;
};
  
}  // namespace lizz

#endif  // LIZZ_TRACK_H_
