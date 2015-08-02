include_directories(${BOOST_INCLUDEDIR})

add_library(lizz
  # Interfaces
  client_interface.h
  search_engine_interface.h

  # Spotify
  spotify/client.cc
  spotify/client.h
  spotify/search_engine.cc
  spotify/search_engine.h

  # Common
  common/search_result.cc
  common/search_result.h
  common/light_http_server.cc
  common/light_http_server.h
  common/log.h

  # Common Error
  common/error/conversion.cc
  common/error/conversion.h

  # Common Future
  common/future.h
  common/future/utils.h
)

target_link_libraries(lizz
  cpprest
  ${Boost_LIBRARIES}
)