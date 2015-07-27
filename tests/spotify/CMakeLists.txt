# Find the QtWidgets library
find_package(Qt5Widgets)
include_directories(${Qt5Widgets_INCLUDE_DIRS})

add_executable(spotify_test
  spotify_test.cc)

add_definitions(-DSPOTIFY_CLIENT_ID="${SPOTIFY_CLIENT_ID}")
add_definitions(-DSPOTIFY_CLIENT_SECRET="${SPOTIFY_CLIENT_SECRET}")
add_definitions(-DSPOTIFY_REDIRECT_URI_PORT="${SPOTIFY_REDIRECT_URI_PORT}")

target_link_libraries(spotify_test
  gtest
  gtest_main
  lizz
  Qt5::Widgets
)
