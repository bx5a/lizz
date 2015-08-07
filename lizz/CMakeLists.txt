include_directories(${BOOST_INCLUDEDIR})

AddTarget(
  lizz

  TYPE
    library

  SOURCES
    # Interfaces
    interfaces/client_interface.h
    interfaces/search_engine_interface.h
    interfaces/track_interface.h
    interfaces/album_interface.h
    interfaces/artist_interface.h
    interfaces/playlist_interface.h

    # Spotify
    spotify/client.cc
    spotify/client.h
    spotify/search_engine.cc
    spotify/search_engine.h

    spotify/object.cc
    spotify/object.h

    spotify/track.h
    spotify/track.cc
    spotify/album.h
    spotify/album.cc
    spotify/artist.h
    spotify/artist.cc
    spotify/playlist.h
    spotify/playlist.cc

    # Common
    common/search_result.cc
    common/search_result.h
    common/light_http_server.cc
    common/light_http_server.h

    # Common Error
    common/error/conversion.cc
    common/error/conversion.h

    # Common Future
    common/future.h
    common/future/utils.h

    # Common Utils 
    common/utils/log.h
    common/utils/string.h
    common/utils/string.cc

  LINK
    cpprest
    ${Boost_LIBRARIES}

  STATIC
)
