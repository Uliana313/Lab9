#pragma once
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "Race.h"
class Leaderboard {
public:
    explicit Leaderboard(std::vector<Race> races) : races_(std::move(races)) {}
    std::map<std::string, int> driverResults() const;
    std::vector<std::string> driverRankings() const;
private:
    std::vector<Race> races_;
};