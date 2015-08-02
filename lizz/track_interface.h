#ifndef LIZZ_TRACK_INTERFACE_H_
#define LIZZ_TRACK_INTERFACE_H_

#include <string>
#include <system_error>

namespace lizz {
  
class TrackInterface {
 public:
  virtual std::string GetName(std::error_code& err) const = 0;
};
  
}  // namespace lizz

#endif  // LIZZ_TRACK_INTERFACE_H_
