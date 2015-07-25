include_directories(${BOOST_INCLUDEDIR})

add_library(lizz
  client_interface.h

  spotify/client.cc
  spotify/client.h

  common/light_http_server.cc
  common/light_http_server.h
  common/log.h
  common/error/conversion.cc
  common/error/conversion.h
)

target_link_libraries(lizz
  cpprest
  ${Boost_LIBRARIES}
)