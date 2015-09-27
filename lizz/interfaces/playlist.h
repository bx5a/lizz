#ifndef LIZZ_PLAYLIST_H_
#define LIZZ_PLAYLIST_H_

namespace lizz {
class Track;
class Playlist {
 public:
  virtual std::string GetDescription(std::error_code& err) const = 0;
  virtual std::string GetName(std::error_code& err) const = 0;
  virtual std::list<std::shared_ptr<Track>> GetTracks(std::error_code& err) const = 0;
};
}  // namespace lizz

#endif  // LIZZ_PLAYLIST_H_
