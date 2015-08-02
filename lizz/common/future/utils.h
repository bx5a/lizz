#ifndef LIZZ_COMMON_FUTURE_UTILS_H_
#define LIZZ_COMMON_FUTURE_UTILS_H_

#include <future>
#include <system_error>
#include <functional>

#include <pplx/pplxtasks.h>

#include "common/future.h"

// TODO(bx5a): find a way to auto detect the template parameter

namespace lizz {
  
template<class ReturnType>
Future<ReturnType> make_std_future(std::function<ReturnType(std::error_code&)> fn) {
  
  auto create_future = [&fn](std::error_code& err){
    return std::make_shared<std::future<ReturnType>>(
               std::async(
                   std::launch::async,
                   std::bind(fn, ref(err))
               )
           );
  };
  
  auto p_generic_task =
      std::make_shared<GenericFuture<std::future<ReturnType>>>(create_future);
  
  return Future<ReturnType>(p_generic_task);
}
  
  
template <class ReturnType>
Future<ReturnType> make_pplx_future(
    std::function<pplx::task<ReturnType>(std::error_code&)> fn) {
  
  auto create_future = [&fn] (std::error_code& err) {
    return std::make_shared<pplx::task<ReturnType>>(fn(err));
  };
  
  auto p_generic_task = std::make_shared<
                            GenericFuture<
                                pplx::task<
                                    ReturnType
                                >
                             >
                          >(create_future);
  
  return Future<ReturnType>(p_generic_task);
}

}  // namespace lizz




#endif  // LIZZ_COMMON_FUTURE_UTILS_H_
