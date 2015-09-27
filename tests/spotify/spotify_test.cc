#include "gtest/gtest.h"

#include <list>

#include <QDesktopServices>
#include <QUrl>
#include <QString>
#include <QApplication>

#include "spotify/spotify_client.h"
#include "spotify/spotify_object.h"
#include "interfaces/search_engine.h"

// TODO(bx5a): Use boost::python and selenium to automate that test

std::shared_ptr<lizz::spotify::SpotifyClient> Login() {
  //Init Qt application
  int argc = 0;
  char** argv = nullptr;
  QApplication app(argc, argv);
  
  std::error_code err;
  uint16_t redirect_uri_port;
  std::stringstream ss(SPOTIFY_REDIRECT_URI_PORT);
  ss >> redirect_uri_port;
  auto p_client = std::make_shared<lizz::spotify::SpotifyClient>(SPOTIFY_CLIENT_ID,
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

TEST(SpotifyTest, Login) {
  // TODO(bx5a): test parallel access to token
  auto p_client = Login();
  std::string type, token;
  std::error_code err;
  static_cast<lizz::spotify::SpotifyClient*>(p_client.get())->QueryAccessToken(&type,
                                                                        &token,
                                                                        err);
  ASSERT_FALSE(err);
  static_cast<lizz::spotify::SpotifyClient*>(p_client.get())->QueryAccessToken(&type,
                                                                        &token,
                                                                        err);
  ASSERT_FALSE(err);
  static_cast<lizz::spotify::SpotifyClient*>(p_client.get())->QueryAccessToken(&type,
                                                                        &token,
                                                                        err);
  ASSERT_FALSE(err);
}


TEST(SpotifyTest, Search) {
  auto p_client = Login();
  auto p_search_engine = p_client->GetSearchEngine();
  {
    auto result = p_search_engine->Run("The who", 2, 0, 0, 0);
    result.Wait();
  
    EXPECT_FALSE(result.GetError());
    EXPECT_EQ(result.Get().GetTracks().size(), 2);
  }
  
  {
    auto result = p_search_engine->Run("The who", 0, 2, 0, 0);
    result.Wait();
    
    EXPECT_FALSE(result.GetError());
    EXPECT_EQ(result.Get().GetAlbums().size(), 2);
  }
  
  {
    auto result = p_search_engine->Run("The who", 0, 0, 2, 0);
    result.Wait();
    
    EXPECT_FALSE(result.GetError());
    EXPECT_EQ(result.Get().GetArtists().size(), 2);
  }
  
  {
    auto result = p_search_engine->Run("The who", 0, 0, 0, 2);
    result.Wait();
    
    EXPECT_FALSE(result.GetError());
    EXPECT_EQ(result.Get().GetPlaylists().size(), 2);
  }
  {
    auto result = p_search_engine->Run("The who", 1, 2, 3, 4);
    result.Wait();
    
    EXPECT_FALSE(result.GetError());
    EXPECT_EQ(result.Get().GetTracks().size(), 1);
    EXPECT_EQ(result.Get().GetAlbums().size(), 2);
    EXPECT_EQ(result.Get().GetArtists().size(), 3);
    EXPECT_EQ(result.Get().GetPlaylists().size(), 4);
  }
}

TEST(SpotifyTest, Object) {
  std::string json = R"test_json(
  {
    "some_int": 10,
    "some_string": "some string",
    "some_bool": true,
    "int_list": [ 2, 142, 0 ],
    "objects": [
      {
        "some_int": 10,
        "some_string": "first string",
        "some_bool": true
      }, {
        "some_int": 10,
        "some_string": "second string",
        "some_bool": true
      }
    ]
  }
  )test_json";
  
  lizz::spotify::SpotifyObject obj;
  std::error_code err;
  obj.Init(json, err);
  ASSERT_FALSE(err);
  
  ASSERT_EQ(obj.GetString("some_string", err), "some string");
  ASSERT_EQ(obj.GetUInt8("some_int", err), 10);
  ASSERT_EQ(obj.GetUInt16("some_int", err), 10);
  ASSERT_TRUE(obj.GetBool("some_bool", err));
  
  ASSERT_EQ(obj.GetStringList("int_list", err).size(), 3);
  ASSERT_EQ((*std::begin(obj.GetObjectList("objects", err)))->GetString("some_string", err), "first string");
}
