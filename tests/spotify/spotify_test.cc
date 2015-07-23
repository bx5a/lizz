#include "gtest/gtest.h"
#include "spotify/client.h"

TEST(SpotifyTest, Login) {
  std::error_code err;
  auto p_client = lizz::spotify::Client::Login("username", "password", err);
  EXPECT_FALSE(err);
}
