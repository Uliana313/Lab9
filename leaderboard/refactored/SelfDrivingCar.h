#pragma once
#include "Driver.h"
class SelfDrivingCar : public Driver {
public:
    SelfDrivingCar(std::string algorithmVersion, std::string country)
        : Driver("", std::move(country)), algorithmVersion_(std::move(algorithmVersion)) {
    }

    std::string displayName() const override {
        return "Self Driving Car - " + country() + " (" + algorithmVersion_ + ")";
    }
    const std::string& algorithmVersion() const { return algorithmVersion_; }

private:
    std::string algorithmVersion_;
};