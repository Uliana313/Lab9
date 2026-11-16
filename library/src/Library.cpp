#include "Library.h"

Library::Library(IBookRepository& repository, IBookNotifier& notifier)
    : repository_(repository), notifier_(notifier) {
}

void Library::addBook(const Book& book) {
    books_.push_back(book);
    repository_.save(book);
    notifier_.notifyBookAdded(book);
}

void Library::displayBooks(std::ostream& out) const {
    for (const auto& book : books_)
        out << "Title: " << book.title() << ", Author: " << book.author() << std::endl;
}