// Ці тести пишуться ДО рефакторингу і мають проходити і на legacy, і на refactored.
#include "mini_test.h"
#include "Driver.h"
#include "SelfDrivingCar.h"
#include "Race.h"
#include "Leaderboard.h"

static const Driver alice("Alice", "UA");
static const Driver bob("Bob", "PL");
static const Driver carl("Carl", "DE");
static const SelfDrivingCar bot("1.2", "US");

using Drivers = std::vector<const Driver*>;

TEST(Leaderboard, SingleRacePointsAre25_18_15) {
    Leaderboard lb({ Race("R1", Drivers{ &alice, &bob, &carl }) });
    auto r = lb.driverResults();
    EXPECT_EQ(r["Alice"], 25);
    EXPECT_EQ(r["Bob"], 18);
    EXPECT_EQ(r["Carl"], 15);
}
TEST(Leaderboard, PointsAreSummedAcrossRaces) {
    Leaderboard lb({ Race("R1", Drivers{ &alice, &bob, &carl }), Race("R2", Drivers{ &bob, &alice, &carl }) });
    auto r = lb.driverResults();
    EXPECT_EQ(r["Alice"], 43);
    EXPECT_EQ(r["Bob"], 43);
    EXPECT_EQ(r["Carl"], 30);
}
TEST(Leaderboard, RankingsSortedByPointsDescending) {
    Leaderboard lb({ Race("R1", Drivers{ &carl, &alice, &bob }) });
    std::vector<std::string> expected{ "Carl", "Alice", "Bob" };
    EXPECT_TRUE(lb.driverRankings() == expected);
}
TEST(Leaderboard, SelfDrivingCarNameFormat) {
    Leaderboard lb({ Race("R1", Drivers{ &bot, &alice }) });
    auto r = lb.driverResults();
    EXPECT_EQ(r["Self Driving Car - US (1.2)"], 25);
    EXPECT_EQ(r["Alice"], 18);
}
TEST(Leaderboard, EmptyLeaderboardHasNoResults) {
    Leaderboard lb({});
    EXPECT_TRUE(lb.driverResults().empty());
    EXPECT_TRUE(lb.driverRankings().empty());
}
TEST(Leaderboard, RaceWithOneDriverGives25) {
    Leaderboard lb({ Race("R1", Drivers{ &bob }) });
    EXPECT_EQ(lb.driverResults()["Bob"], 25);
}
TEST(Leaderboard, SameDriverInManyRacesAccumulates) {
    Leaderboard lb({ Race("R1", Drivers{ &alice }), Race("R2", Drivers{ &alice }), Race("R3", Drivers{ &alice }) });
    EXPECT_EQ(lb.driverResults()["Alice"], 75);
}