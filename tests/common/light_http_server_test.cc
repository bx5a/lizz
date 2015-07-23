#include "gtest/gtest.h"
#include "common/light_http_server.h"

#include <iostream>

TEST(LightHttpServerTest, Start) {
  lizz::LightHttpServer server;
  
  std::error_code err;
  server.Start(8080, err);
  
  EXPECT_FALSE(err);
  auto handler = [](const std::string& request,
                    std::error_code& err){
    std::cout<<request<<std::endl;
    return "HTTP/1.1 200 OK";
  };
  
  server.SetHandler(handler);
  
  std::this_thread::sleep_for(std::chrono::seconds(20));
};
