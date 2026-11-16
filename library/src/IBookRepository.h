#pragma once
#include "Book.h"

// Абстракція «куди зберігати книгу» (DIP).
class IBookRepository {
public:
    virtual ~IBookRepository() = default;
    virtual void save(const Book& book) = 0;
};