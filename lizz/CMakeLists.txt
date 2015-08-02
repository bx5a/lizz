include_directories(${BOOST_INCLUDEDIR})

AddTarget(
  lizz

  TYPE
    library

  SOURCES
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

  LINK
    cpprest
    ${Boost_LIBRARIES}

  STATIC
)
