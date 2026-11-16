#include "Leaderboard.h"
#include <algorithm>

std::map<std::string, int> Leaderboard::driverResults() const {
    std::map<std::string, int> results;
    for (const auto& race : races_) {
        for (std::size_t i = 0; i < race.getResults().size(); ++i) {
            std::string name = race.getDriverName(race.getResults()[i]);
            int points = Race::POINTS[i];            // UB, якщо гонщиків > 3
            if (results.count(name)) results[name] += points;
            else results[name] = points;
        }
    }
    return results;
}

std::vector<std::string> Leaderboard::driverRankings() const {
    auto results = driverResults();
    std::vector<std::string> names;
    for (const auto& kv : results) names.push_back(kv.first);
    std::sort(names.begin(), names.end(),
        [&](const std::string& a, const std::string& b) { return results[a] > results[b]; });
    return names;
}