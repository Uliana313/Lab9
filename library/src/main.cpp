#include <iostream>
#include "Library.h"
#include "ConsoleServices.h"

int main() {
    ConsoleBookRepository repository;
    ConsoleEmailNotifier  notifier;
    Library library(repository, notifier);

    library.addBook(Book{ "The Catcher in the Rye", "J.D. Salinger" });
    library.addBook(Book{ "To Kill a Mockingbird", "Harper Lee" });
    library.displayBooks(std::cout);
    return 0;
}