# Find the QtWidgets library
find_package(Qt5Widgets)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${BOOST_INCLUDEDIR})

add_definitions(-DSPOTIFY_CLIENT_ID="${SPOTIFY_CLIENT_ID}")
add_definitions(-DSPOTIFY_CLIENT_SECRET="${SPOTIFY_CLIENT_SECRET}")
add_definitions(-DSPOTIFY_REDIRECT_URI_PORT="${SPOTIFY_REDIRECT_URI_PORT}")

AddTarget(
  spotify_test
  TYPE
    executable
  SOURCES
    spotify_test.cc
  LINK
    gtest
    gtest_main
    lizz
    Qt5::Widgets
)
