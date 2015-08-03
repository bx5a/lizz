#include "gtest/gtest.h"

#include <QDesktopServices>
#include <QUrl>
#include <QString>
#include <QApplication>

#include "spotify/client.h"
#include "spotify/track.h"
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

TEST(SpotifyTest, Login) {
  // TODO(bx5a): test parallel access to token
  auto p_client = Login();
  std::string type, token;
  std::error_code err;
  static_cast<lizz::spotify::Client*>(p_client.get())->QueryAccessToken(&type,
                                                                        &token,
                                                                        err);
  ASSERT_FALSE(err);
  static_cast<lizz::spotify::Client*>(p_client.get())->QueryAccessToken(&type,
                                                                        &token,
                                                                        err);
  ASSERT_FALSE(err);
  static_cast<lizz::spotify::Client*>(p_client.get())->QueryAccessToken(&type,
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

TEST(SpotifyTest, Track) {
  auto p_client = Login();
  auto p_search_engine = p_client->GetSearchEngine();
  auto result = p_search_engine->Run("The who", 1, 0, 0, 0);
  result.Wait();
  
  EXPECT_FALSE(result.GetError());
  ASSERT_EQ(result.Get().GetTracks().size(), 1);
  
  std::shared_ptr<lizz::TrackInterface> track_ptr = *(result.Get().GetTracks().begin());
  auto p_track = static_cast<lizz::spotify::Track*>(track_ptr.get());
  
  std::error_code err;
  
  // Spotify specific
  auto markets = p_track->GetAvailableMarkets(err);
  EXPECT_EQ(markets.size(), 2);
  EXPECT_EQ(*(markets.begin()), "DK");
  EXPECT_FALSE(p_track->GetExplicit(err));
  EXPECT_EQ(p_track->GetDiscNumber(err), 1);
  EXPECT_EQ(p_track->GetHref(err), "https://api.spotify.com/v1/tracks/4jGEwDE6F6ERJ3BxAZ03sU");
  EXPECT_EQ(p_track->GetId(err), "4jGEwDE6F6ERJ3BxAZ03sU");
  EXPECT_EQ(p_track->GetPopularity(err), 0);
  EXPECT_EQ(p_track->GetUri(err), "spotify:track:4jGEwDE6F6ERJ3BxAZ03sU");
  
  // global
  EXPECT_EQ(track_ptr->GetTrackNumber(err), 105);
  EXPECT_EQ(track_ptr->GetDuration(err), std::chrono::milliseconds(242186));
  EXPECT_EQ(track_ptr->GetArtists(err).size(), 1);
  EXPECT_EQ(track_ptr->GetName(err), "I Wanna Dance With Somebody (Who Loves Me) (Glee Cast Version)");
}
