#pragma once
#include "Book.h"

// Абстракція «як повідомити про нову книгу» (DIP).
class IBookNotifier {
public:
    virtual ~IBookNotifier() = default;
    virtual void notifyBookAdded(const Book& book) = 0;
};