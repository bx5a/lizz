#ifndef LIZZ_COMMON_ERROR_CONVERSION_H_
#define LIZZ_COMMON_ERROR_CONVERSION_H_

#include <system_error>
#include <boost/system/error_code.hpp>

namespace lizz {
  
void ToBoostError(const std::error_code& std_err,
                  boost::system::error_code& boost_err);
void FromBoostError(const boost::system::error_code& boost_err,
                    std::error_code& std_err);
  
}  // namespace lizz

#endif  // LIZZ_COMMON_ERROR_CONVERSION_H_
