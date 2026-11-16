#include "Leaderboard.h"
#include <algorithm>

std::map<std::string, int> Leaderboard::driverResults() const {
    std::map<std::string, int> totals;
    for (const auto& race : races_) {
        const auto& order = race.getResults();
        for (std::size_t position = 0; position < order.size(); ++position)
            totals[order[position]->displayName()] += points_->pointsForPosition(position);
    }
    return totals;
}

std::vector<std::string> Leaderboard::driverRankings() const {
    const auto totals = driverResults();
    std::vector<std::string> names;
    names.reserve(totals.size());
    for (const auto& entry : totals) names.push_back(entry.first);
    std::stable_sort(names.begin(), names.end(), [&](const std::string& a, const std::string& b) {
        return totals.at(a) > totals.at(b);       // names вже відсортовані за алфавітом → tie-break
        });
    return names;
}