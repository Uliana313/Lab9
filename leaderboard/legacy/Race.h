#pragma once
#include <string>
#include <vector>
#include "Driver.h"
class Race {
public:
    static const int POINTS[3];                      // жорстко закодовані очки
    Race(std::string name, std::vector<const Driver*> results);
    const std::vector<const Driver*>& getResults() const;
    std::string getDriverName(const Driver* driver) const;
private:
    std::string name_;
    std::vector<const Driver*> results_;
};