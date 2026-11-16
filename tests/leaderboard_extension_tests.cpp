// Тести індивідуального розширення (лише для refactored).
#include <memory>
#include "mini_test.h"
#include "Driver.h"
#include "SelfDrivingCar.h"
#include "Race.h"
#include "Leaderboard.h"

static const Driver a("Anna", "UA"), b("Boris", "PL"), c("Clara", "DE"), d("Dan", "FR"), e("Eva", "ES");
using Drivers = std::vector<const Driver*>;

TEST(Extension, FourthPlaceGetsZeroInsteadOfUndefinedBehaviour) {
    Leaderboard lb({ Race("R", Drivers{ &a, &b, &c, &d, &e }) });
    auto r = lb.driverResults();
    EXPECT_EQ(r["Dan"], 0);
    EXPECT_EQ(r["Eva"], 0);
}
TEST(Extension, CustomPointsSystemIsUsed) {
    auto pts = std::make_shared<TablePointsSystem>(std::vector<int>{10, 6, 4, 3, 2});
    Leaderboard lb({ Race("R", Drivers{ &a, &b, &c, &d, &e }) }, pts);
    auto r = lb.driverResults();
    EXPECT_EQ(r["Anna"], 10);
    EXPECT_EQ(r["Dan"], 3);
    EXPECT_EQ(r["Eva"], 2);
}
TEST(Extension, TieIsBrokenAlphabetically) {
    Leaderboard lb({ Race("R1", Drivers{ &b, &a }), Race("R2", Drivers{ &a, &b }) });   // рівні очки: 43/43
    std::vector<std::string> expected{ "Anna", "Boris" };
    EXPECT_TRUE(lb.driverRankings() == expected);
}
TEST(Extension, DisplayNameIsPolymorphic) {
    SelfDrivingCar car("2.0", "JP");
    const Driver& base = car;
    EXPECT_EQ(base.displayName(), std::string("Self Driving Car - JP (2.0)"));
}
TEST(Extension, ZeroPointsTablePossible) {
    auto pts = std::make_shared<TablePointsSystem>(std::vector<int>{});
    Leaderboard lb({ Race("R", Drivers{ &a }) }, pts);
    EXPECT_EQ(lb.driverResults()["Anna"], 0);
}