#include "gtest/gtest.h"

#include <QDesktopServices>
#include <QUrl>
#include <QString>
#include <QApplication>

#include "spotify/client.h"
#include "search_engine_interface.h"

// TODO(bx5a): Use boost::python and selenium to automate that test

std::shared_ptr<lizz::spotify::Client> Login() {
  //Init Qt application
  int argc = 0;
  char** argv = nullptr;
  QApplication app(argc, argv);
  
  std::error_code err;
  uint16_t redirect_uri_port;
  std::stringstream ss(SPOTIFY_REDIRECT_URI_PORT);
  ss >> redirect_uri_port;
  auto p_client = std::make_shared<lizz::spotify::Client>(SPOTIFY_CLIENT_ID,
                                                          SPOTIFY_CLIENT_SECRET,
                                                          redirect_uri_port);
  
  auto login_handler = [](const std::string& login_page_url){
    QUrl url(QString(login_page_url.c_str()));
    QDesktopServices::openUrl(url);
  };
  
  auto login_completion_handler = [](const std::error_code& err) {
    EXPECT_FALSE(err);
    
    const std::string close_webpage_script = R"html_code(
    <script language="javascript" type="text/javascript">
    window.close();
    </script>
    )html_code";
    
    
    std::string header_code =
    "HTTP/1.1 200 OK\r\n"
    "Content-Length=" + std::to_string(close_webpage_script.size()) + "\r\n"
    "\r\n\r\n";
    
    return header_code + close_webpage_script;
  };
  
  p_client->Login(login_handler, login_completion_handler, 60, err);
  EXPECT_FALSE(err);
  return p_client;
}

TEST(SpotifyTest, Search) {
  auto p_client = Login();
  auto p_search_engine = p_client->GetSearchEngine();
  auto result = p_search_engine->Run("The who", 0, 0, 1, 0);
  result.Wait();
  
  EXPECT_FALSE(result.GetError());
}
