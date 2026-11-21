#include <gtest/gtest.h>

#include "duration.h"

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
