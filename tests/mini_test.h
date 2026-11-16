#pragma once
// Мінімальний аналог GoogleTest (без встановлення залежностей).
// TEST(Suite, Name) { EXPECT_EQ(a, b); EXPECT_TRUE(x); }
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace mini {
    struct Case { std::string name; std::function<void()> fn; };
    inline std::vector<Case>& registry() { static std::vector<Case> r; return r; }
    inline int& failures() { static int f = 0; return f; }
    struct Registrar { Registrar(const std::string& n, std::function<void()> f) { registry().push_back({ n, std::move(f) }); } };
    inline int runAll() {
        int bad = 0;
        for (auto& c : registry()) {
            int before = failures();
            c.fn();
            bool ok = failures() == before;
            std::cout << (ok ? "[  OK  ] " : "[ FAIL ] ") << c.name << "\n";
            if (!ok) ++bad;
        }
        std::cout << registry().size() - bad << "/" << registry().size() << " tests passed\n";
        return bad == 0 ? 0 : 1;
    }
    template <class A, class B>
    void expectEq(const A& a, const B& b, const char* ea, const char* eb, const char* file, int line) {
        if (!(a == b)) {
            ++failures();
            std::cout << file << ":" << line << ": EXPECT_EQ(" << ea << ", " << eb << ") failed\n";
        }
    }
}  // namespace mini

#define TEST(suite, name) \
    static void suite##_##name(); \
    static mini::Registrar reg_##suite##_##name(#suite "." #name, suite##_##name); \
    static void suite##_##name()
#define EXPECT_EQ(a, b) mini::expectEq((a), (b), #a, #b, __FILE__, __LINE__)
#define EXPECT_TRUE(x)  do { if (!(x)) { ++mini::failures(); std::cout << __FILE__ << ":" << __LINE__ << ": EXPECT_TRUE(" #x ") failed\n"; } } while (0)