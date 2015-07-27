#include "gtest/gtest.h"
#include "spotify/client.h"

#include <QDesktopServices>
#include <QUrl>
#include <QString>
#include <QApplication>

TEST(SpotifyTest, Login) {
  //Init Qt application
  int argc = 0;
  char** argv = nullptr;
  QApplication app(argc, argv);
  
  std::error_code err;
  uint16_t redirect_uri_port;
  std::stringstream ss(SPOTIFY_REDIRECT_URI_PORT);
  ss >> redirect_uri_port;
  lizz::spotify::Client client(SPOTIFY_CLIENT_ID,
                               SPOTIFY_CLIENT_SECRET,
                               redirect_uri_port);
  
  auto login_handler = [](const std::string& login_page_url){
    QUrl url(QString(login_page_url.c_str()));
    QDesktopServices::openUrl(url);
  };
  
  client.Login(login_handler, 60, err);
  EXPECT_FALSE(err);
}
