#include "gtest/gtest.h"

#include <iostream>
#include <system_error>

#include <cpprest/http_client.h>

#include "common/future.h"
#include "common/future/utils.h"

TEST(FutureTest, StdFuture) {
  auto fn = [](std::error_code& err) -> int {
    err = std::make_error_code(std::errc::bad_message);
    return 0;
  };
  auto future = lizz::make_std_future<int>(fn);
  
  future.Wait();
  ASSERT_TRUE(future.GetError());
  ASSERT_EQ(future.Get(), 0);
}

TEST(FutureTest, PplxTask) {
  web::http::client::http_client google_client("http://www.google.com");
  
  auto fn = [&google_client](std::error_code& err) {
    auto request = google_client.request(web::http::methods::GET)
    
    .then([&err](web::http::http_response response){
      return response.extract_string();
    })
    
    .then([&err](utility::string_t str) -> int {
      err = std::make_error_code(std::errc::bad_message);
      return 0;
    });
    
    return request;
  };
  
  auto future = lizz::make_pplx_future<int>(fn);
  
  future.Wait();
  ASSERT_TRUE(future.GetError());
  ASSERT_EQ(future.Get(), 0);
}
