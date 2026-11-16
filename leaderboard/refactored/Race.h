#pragma once
#include <string>
#include <utility>
#include <vector>
#include "Driver.h"
class Race {
public:
    Race(std::string name, std::vector<const Driver*> results)
        : name_(std::move(name)), results_(std::move(results)) {
    }
    const std::string& name() const { return name_; }
    const std::vector<const Driver*>& getResults() const { return results_; }
private:
    std::string name_;
    std::vector<const Driver*> results_;
};