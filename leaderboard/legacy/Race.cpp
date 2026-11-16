#include "Race.h"
#include "SelfDrivingCar.h"

const int Race::POINTS[3] = { 25, 18, 15 };

Race::Race(std::string name, std::vector<const Driver*> results)
    : name_(std::move(name)), results_(std::move(results)) {
}

const std::vector<const Driver*>& Race::getResults() const { return results_; }

// «Запах»: перевірка типу через dynamic_cast замість поліморфізму
std::string Race::getDriverName(const Driver* driver) const {
    if (auto car = dynamic_cast<const SelfDrivingCar*>(driver))
        return "Self Driving Car - " + car->country + " (" + car->algorithmVersion + ")";
    return driver->name;
}