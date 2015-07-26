#include "gtest/gtest.h"

#include <iostream>

#include <cpprest/http_client.h>

#include "common/light_http_server.h"

TEST(LightHttpServerTest, Start) {
  lizz::LightHttpServer server;
  
  std::error_code err;
  server.Init(8080, err);
  EXPECT_FALSE(err);
  
  server.Start();
  std::string obtained_content;
  int call_count = 0;
  auto handler = [&call_count, &obtained_content](std::string&& request_header,
                                                  std::string&& request_content,
                                                  std::error_code& err){
    obtained_content = request_content;
    call_count++;
    return "HTTP/1.1 200 OK\r\n\r\n";
  };
  server.SetHandler(handler);
  
  // query localhost::8080 and check if request match
  web::http::client::http_client client("http://localhost:8080");
  std::string body_content("This is some body content");
  client.request(web::http::methods::GET, "", body_content).wait();
  ASSERT_EQ(obtained_content, body_content);
  
  std::string body_content2("This is another content");
  client.request(web::http::methods::GET, "", body_content2).wait();
  ASSERT_EQ(obtained_content, body_content2);
  ASSERT_EQ(call_count, 2);
};
