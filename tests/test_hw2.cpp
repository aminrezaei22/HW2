#include <gtest/gtest.h>

#include "duration.h"
#include "playlist.h"
#include "track.h"

TEST(DurationConstructor, DefaultIsZero) {
    EXPECT_EQ(Duration().total_seconds(), 0);
}

TEST(DurationConstructor, CombinesMinutesAndSeconds) {
    EXPECT_EQ(Duration(3, 5).total_seconds(), 185);
}

TEST(DurationConstructor, SecondsPast59CarryIntoMinutes) {
    EXPECT_EQ(Duration(0, 75).total_seconds(), 75);
    EXPECT_EQ(Duration(2, 60).total_seconds(), 180);
}

TEST(DurationConstructor, NegativeSecondsTakeFromMinutes) {
    EXPECT_EQ(Duration(1, -30).total_seconds(), 30);
}

TEST(DurationConstructor, NegativeTotalClampsToZero) {
    EXPECT_EQ(Duration(0, -5).total_seconds(), 0);
    EXPECT_EQ(Duration(-2, 10).total_seconds(), 0);
}

TEST(PlaylistConstructor, StartsEmpty) {
    Playlist playlist(3);
    EXPECT_EQ(playlist.size(), 0);
}

TEST(PlaylistConstructor, CapacityBelowOneBecomesOne) {
    Playlist zero(0);
    EXPECT_TRUE(zero.add_track({"Only", Duration(1, 0)}));
    EXPECT_FALSE(zero.add_track({"Extra", Duration(1, 0)}));
    EXPECT_EQ(zero.size(), 1);

    Playlist negative(-3);
    EXPECT_TRUE(negative.add_track({"Only", Duration(1, 0)}));
    EXPECT_FALSE(negative.add_track({"Extra", Duration(1, 0)}));
    EXPECT_EQ(negative.size(), 1);
}

TEST(AddTrack, StoresTrackAndGrowsSize) {
    Playlist playlist(2);
    EXPECT_TRUE(playlist.add_track({"Static", Duration(2, 58)}));
    EXPECT_EQ(playlist.size(), 1);
}

TEST(AddTrack, FullPlaylistRefusesTrack) {
    Playlist playlist(2);
    EXPECT_TRUE(playlist.add_track({"First", Duration(1, 0)}));
    EXPECT_TRUE(playlist.add_track({"Second", Duration(2, 0)}));
    EXPECT_FALSE(playlist.add_track({"Third", Duration(3, 0)}));
    EXPECT_EQ(playlist.size(), 2);
}

TEST(AddTrack, EmptyTitleIsRefused) {
    Playlist playlist(2);
    EXPECT_FALSE(playlist.add_track({"", Duration(1, 0)}));
    EXPECT_EQ(playlist.size(), 0);
}

TEST(FindTrack, FindsStoredTrack) {
    Playlist playlist(3);
    playlist.add_track({"Neon Rain", Duration(4, 5)});
    playlist.add_track({"Static", Duration(2, 58)});
    const Track* found = playlist.find_track("Static");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->title, "Static");
    EXPECT_EQ(found->length.total_seconds(), 178);
}

TEST(FindTrack, ReturnsFirstOfMatchingTitles) {
    Playlist playlist(2);
    playlist.add_track({"Static", Duration(2, 58)});
    playlist.add_track({"Static", Duration(9, 0)});
    const Track* found = playlist.find_track("Static");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(found->length.total_seconds(), 178);
}

TEST(FindTrack, MissingTitleReturnsNull) {
    Playlist playlist(2);
    playlist.add_track({"Static", Duration(2, 58)});
    EXPECT_EQ(playlist.find_track("Missing"), nullptr);
    EXPECT_EQ(playlist.find_track("static"), nullptr);
}

TEST(FindTrack, EmptyPlaylistReturnsNull) {
    Playlist playlist(2);
    EXPECT_EQ(playlist.find_track("Static"), nullptr);
}
