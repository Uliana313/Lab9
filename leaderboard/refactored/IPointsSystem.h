#pragma once
#include <cstddef>
#include <utility>
#include <vector>

// Стратегія нарахування очок (OCP: нові системи без зміни Leaderboard).
class IPointsSystem {
public:
    virtual ~IPointsSystem() = default;
    virtual int pointsForPosition(std::size_t position) const = 0;   // position: 0 = перше місце
};

class TablePointsSystem : public IPointsSystem {
public:
    explicit TablePointsSystem(std::vector<int> table) : table_(std::move(table)) {}
    int pointsForPosition(std::size_t position) const override {
        return position < table_.size() ? table_[position] : 0;      // за межами таблиці — 0, без UB
    }
private:
    std::vector<int> table_;
};

// Класична система kata: 25, 18, 15
class ClassicPointsSystem : public TablePointsSystem {
public:
    ClassicPointsSystem() : TablePointsSystem({ 25, 18, 15 }) {}
};