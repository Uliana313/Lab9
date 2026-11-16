#pragma once
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "Race.h"
#include "IPointsSystem.h"

class Leaderboard {
public:
    // Публічний інтерфейс збережено; другий параметр — розширення (стратегія очок).
    explicit Leaderboard(std::vector<Race> races,
        std::shared_ptr<const IPointsSystem> points = std::make_shared<ClassicPointsSystem>())
        : races_(std::move(races)), points_(std::move(points)) {
    }

    std::map<std::string, int> driverResults() const;
    // Сортування: більше очок — вище; при рівності — за назвою (детермінований tie-break).
    std::vector<std::string> driverRankings() const;

private:
    std::vector<Race> races_;
    std::shared_ptr<const IPointsSystem> points_;
};