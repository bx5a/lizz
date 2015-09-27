include_directories(${BOOST_INCLUDEDIR})

AddTarget(
  lizz

  TYPE
    library

  SOURCES
    # Interfaces
    interfaces/client.h
    interfaces/search_engine.h
    interfaces/track.h
    interfaces/album.h
    interfaces/artist.h
    interfaces/playlist.h
    interfaces/fwd.h

    # Spotify
    spotify/spotify_client.cc
    spotify/spotify_client.h
    spotify/spotify_search_engine.cc
    spotify/spotify_search_engine.h

    spotify/spotify_object.cc
    spotify/spotify_object.h

    spotify/spotify_track.h
    spotify/spotify_track.cc
    spotify/spotify_album.h
    spotify/spotify_album.cc
    spotify/spotify_artist.h
    spotify/spotify_artist.cc
    spotify/spotify_playlist.h
    spotify/spotify_playlist.cc

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
