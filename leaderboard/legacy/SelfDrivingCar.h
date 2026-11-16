#pragma once
#include "Driver.h"
class SelfDrivingCar : public Driver {
public:
    SelfDrivingCar(std::string algorithmVersion, std::string country)
        : Driver("", std::move(country)), algorithmVersion(std::move(algorithmVersion)) {
    }
    std::string algorithmVersion;
};