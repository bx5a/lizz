#ifndef LIZZ_COMMON_LOG_H_
#define LIZZ_COMMON_LOG_H_

#include <boost/log/trivial.hpp>

#define LOG(lvl) BOOST_LOG_TRIVIAL(lvl) <<__PRETTY_FUNCTION__ \
                                        << std::endl << " -- "

#endif  // LIZZ_COMMON_LOG_H_
