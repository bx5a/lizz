#ifndef LIZZ_CLIENT_INTERFACE_H_
#define LIZZ_CLIENT_INTERFACE_H_

#include <memory>

namespace lizz {
class SearchEngineInterface;

class ClientInterface {
 public:
  virtual std::shared_ptr<SearchEngineInterface> GetSearchEngine() = 0;
};
 
}  // namespace lizz

#endif  // LIZZ_CLIENT_INTERFACE_H_
