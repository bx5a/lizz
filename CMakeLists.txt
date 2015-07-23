cmake_minimum_required(VERSION 3.1)

project(lizz CXX)
# for c++11 support
if (APPLE)
  add_definitions(-std=c++11)
endif()

option(lizz_unit_test "Enable unit test targets" ON)

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
  STATIC
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
# Don't build tests and samples
set(BUILD_TESTS OFF CACHE BOOL "Build tests.")
set(BUILD_SAMPLES OFF CACHE BOOL "Build samples.")
# Compile as static library
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared Libraries.")
add_subdirectory(thirdparty/casablanca/Release)

if (lizz_unit_test)
  add_subdirectory(thirdparty/googletest)
  include_directories(thirdparty/googletest/include)
  add_subdirectory(./tests)
endif()
