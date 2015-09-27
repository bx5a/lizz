#ifndef LIZZ_CLIENT_H_
#define LIZZ_CLIENT_H_

#include <memory>

namespace lizz {
class SearchEngine;

class Client {
 public:
  virtual std::shared_ptr<SearchEngine> GetSearchEngine() = 0;
};
 
}  // namespace lizz

#endif  // LIZZ_CLIENT_H_
