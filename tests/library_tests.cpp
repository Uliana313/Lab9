#include <sstream>
#include "mini_test.h"
#include "Library.h"

// Підроблені залежності (fake/mock): запам’ятовують, що їх викликали.
struct FakeRepository : IBookRepository {
    std::vector<std::string> saved;
    void save(const Book& b) override { saved.push_back(b.title()); }
};
struct FakeNotifier : IBookNotifier {
    std::vector<std::string> notified;
    void notifyBookAdded(const Book& b) override { notified.push_back(b.title()); }
};

TEST(Library, AddBookStoresBook) {
    FakeRepository r; FakeNotifier n; Library lib(r, n);
    lib.addBook(Book{ "A", "X" });
    EXPECT_EQ(lib.size(), 1u);
}
TEST(Library, AddBookCallsRepositoryAndNotifierOnce) {
    FakeRepository r; FakeNotifier n; Library lib(r, n);
    lib.addBook(Book{ "A", "X" });
    EXPECT_EQ(r.saved.size(), 1u);
    EXPECT_EQ(n.notified.size(), 1u);
    EXPECT_EQ(r.saved[0], std::string("A"));
}
TEST(Library, DisplayBooksFormat) {
    FakeRepository r; FakeNotifier n; Library lib(r, n);
    lib.addBook(Book{ "Dune", "Herbert" });
    std::ostringstream out; lib.displayBooks(out);
    EXPECT_EQ(out.str(), std::string("Title: Dune, Author: Herbert\n"));
}
TEST(Library, DisplayEmptyLibraryPrintsNothing) {
    FakeRepository r; FakeNotifier n; Library lib(r, n);
    std::ostringstream out; lib.displayBooks(out);
    EXPECT_EQ(out.str(), std::string(""));
}
TEST(Library, DisplayDoesNotCallServices) {
    FakeRepository r; FakeNotifier n; Library lib(r, n);
    lib.addBook(Book{ "A", "X" });
    std::ostringstream out; lib.displayBooks(out);
    EXPECT_EQ(r.saved.size(), 1u);
}