add_library(lizz
  client_interface.h

  spotify/client.cc
  spotify/client.h
)

target_link_libraries(lizz
  cpprest
)