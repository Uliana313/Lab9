#pragma once
#include <string>
#include <utility>
class Driver {
public:
    Driver(std::string name, std::string country) : name(std::move(name)), country(std::move(country)) {}
    virtual ~Driver() = default;
    std::string name;      // публічні поля — порушення інкапсуляції
    std::string country;
};