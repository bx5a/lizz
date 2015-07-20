cmake_minimum_required(VERSION 3.1)

project(lizz CXX)
# for c++11 support
if (APPLE)
  add_definitions(-std=c++11)
endif()

add_subdirectory(thirdparty/cmake-helper)

# Include Boost
add_subdirectory(thirdparty/boost)
FindBoost(
  SOURCE_DIR
    ${boost_source_dir}
  COMPONENTS
    random
    chrono
    system
    thread
    regex
    filesystem
)

# Include OpenSSL
add_subdirectory(thirdparty/openssl)
FindOpenSSL(
  SOURCE_DIR
    ${openssl_source_dir}
  MINIMUM_VERSION
    1.0.0
)

# Include Casablanca using the provided CMakeLists.txt
add_subdirectory(thirdparty/casablanca/Release)
