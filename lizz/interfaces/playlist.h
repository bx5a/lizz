#ifndef LIZZ_PLAYLIST_H_
#define LIZZ_PLAYLIST_H_

#include "interfaces/fwd.h"

namespace lizz {
class Track;
class Playlist {
 public:
  virtual std::string GetDescription(std::error_code& err) const = 0;
  virtual std::string GetName(std::error_code& err) const = 0;
  virtual TrackList GetTracks(std::error_code& err) const = 0;
};
}  // namespace lizz

#endif  // LIZZ_PLAYLIST_H_
