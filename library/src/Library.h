#pragma once
#include <cstddef>
#include <ostream>
#include <vector>
#include "Book.h"
#include "IBookRepository.h"
#include "IBookNotifier.h"

// Бібліотека лише керує колекцією книг.
// Збереження та сповіщення отримує ззовні (Dependency Injection).
class Library {
public:
    Library(IBookRepository& repository, IBookNotifier& notifier);

    void addBook(const Book& book);
    void displayBooks(std::ostream& out) const;
    std::size_t size() const { return books_.size(); }

private:
    std::vector<Book> books_;
    IBookRepository& repository_;
    IBookNotifier& notifier_;
};