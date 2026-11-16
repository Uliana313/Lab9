#pragma once
#include <string>
#include <utility>
// Базовий гонщик: поведінка «як мене показувати» — його власна відповідальність.
class Driver {
public:
    Driver(std::string name, std::string country)
        : name_(std::move(name)), country_(std::move(country)) {
    }
    virtual ~Driver() = default;

    virtual std::string displayName() const { return name_; }
    const std::string& country() const { return country_; }

private:
    std::string name_;
    std::string country_;
};