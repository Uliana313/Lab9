#pragma once
#include <iostream>
#include "IBookRepository.h"
#include "IBookNotifier.h"

// Реалізації-«заглушки», що друкують у консоль (як у вихідному коді).
class ConsoleBookRepository : public IBookRepository {
public:
    explicit ConsoleBookRepository(std::ostream& out = std::cout) : out_(out) {}
    void save(const Book&) override { out_ << "Saving book to database...\n"; }
private:
    std::ostream& out_;
};

class ConsoleEmailNotifier : public IBookNotifier {
public:
    explicit ConsoleEmailNotifier(std::ostream& out = std::cout) : out_(out) {}
    void notifyBookAdded(const Book&) override {
        out_ << "Sending email notification about the new book...\n";
    }
private:
    std::ostream& out_;
};