#include "print.h"
#include <gtest/gtest.h>
#include <type_traits>
#include <iostream>
#include <vector>
#include <deque>
#include <array>
#include <list>
#include <iterator>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <tuple>
#include <memory>
#include <bitset>
#include <stack>


int main() {
    RUN_ALL_TESTS();
}

TEST(print, fTypes) {
    std::ostringstream out;

    out.str("");
    print({.file = &out}, 2024);
    EXPECT_EQ(out.str(), "2024\n");

    out.str("");
    print({.file = &out}, -2024);
    EXPECT_EQ(out.str(), "-2024\n");

    out.str("");
    print({.file = &out}, 0);
    EXPECT_EQ(out.str(), "0\n");

    bool b = true;
    out.str("");
    print({.file = &out}, b);
    EXPECT_EQ(out.str(), "True\n");

    double v1 = 23.2;
    out.str("");
    print({.file = &out}, v1);
    EXPECT_EQ(out.str(), "23.2\n");

    char c = 'A';
    out.str("");
    print({.file = &out}, c);
    EXPECT_EQ(out.str(), "A\n");

    std::string s = "Hello World";
    out.str("");
    print({.file = &out}, s);
    EXPECT_EQ(out.str(), "Hello World\n");

    out.str("");
    print({.file = &out});
    EXPECT_EQ(out.str(), "\n");

}

TEST(print, sequenceCcontainers) {
    std::ostringstream out;

    std::vector<int> vc({4, 5, 6});
    out.str("");
    print({.file = &out}, vc);
    EXPECT_EQ(out.str(), "[4, 5, 6]\n");

    std::deque<std::vector<int>> dq({vc, vc});
    out.str("");
    print({.file = &out}, dq);
    EXPECT_EQ(out.str(), "[[4, 5, 6], [4, 5, 6]]\n");

    std::array<std::string, 3> a = {"hello", "world", "......"};
    out.str("");
    print({.file = &out}, a);
    EXPECT_EQ(out.str(), "[hello, world, ......]\n");

    std::list<double> ls({23.1, 6542.34, 114.514});
    out.str("");
    print({.file = &out}, ls);
    EXPECT_EQ(out.str(), "[23.1, 6542.34, 114.514]\n");

    std::forward_list<bool> fl({true, false, true});
    out.str("");
    print({.file = &out}, fl);
    EXPECT_EQ(out.str(), "[True, False, True]\n");

    __int128 v128 = __int128(456153648) * 456153648 * 456153648;
    out.str("");
    print({.file = &out}, v128);
    EXPECT_EQ(out.str(), "94914695150555689776033792\n");

}

TEST(print, arrays) {
    std::ostringstream out;

    int a[3] = {3, 5, 8};
    out.str("");
    print({.file = &out}, a);
    EXPECT_EQ(out.str(), "[3, 5, 8]\n");
}

TEST(print, maps) {
    std::ostringstream out;

    std::map<std::string, int> mp({{"Alice", 100},
                                   {"Bob",   -100}});
    out.str("");
    print({.file = &out}, mp);
    EXPECT_EQ(out.str(), "{Alice: 100, Bob: -100}\n");

    using vm = std::vector<std::map<std::string, int>>;
    vm vc({mp, mp});
    out.str("");
    print({.file = &out}, vc);
    EXPECT_EQ(out.str(), "[{Alice: 100, Bob: -100}, {Alice: 100, Bob: -100}]\n");

    std::multimap<std::string, int> mmp({{"Alice", 114},
                                         {"Bob",   -100},
                                         {"Alice", 514}});
    out.str("");
    print({.file = &out}, mmp);
    EXPECT_EQ(out.str(), "{Alice: 114, Alice: 514, Bob: -100}\n");
}

TEST(print, sets) {
    std::ostringstream out;

    std::set<std::string> st({"Alice", "Bob", "Carol", "Chuck"});
    out.str("");
    print({.file = &out}, st);
    EXPECT_EQ(out.str(), "{Alice, Bob, Carol, Chuck}\n");

    std::multiset<std::string> mst({"A", "A", "B", "C", "D", "B"});
    out.str("");
    print({.file = &out}, mst);
    EXPECT_EQ(out.str(), "{A, A, B, B, C, D}\n");
}

TEST(print, tuples) {
    std::ostringstream out;

    std::tuple<int, std::string, bool, int> tp({10, "Alice", true, -214});
    out.str("");
    print({.file = &out}, tp);
    EXPECT_EQ(out.str(), "(10, Alice, True, -214)\n");

    std::pair<int, std::string> pa(10, "Alice");
    out.str("");
    print({.file = &out}, pa);
    EXPECT_EQ(out.str(), "(10, Alice)\n");
}

TEST(print, enumeration) {
    std::ostringstream out;

    enum class Color {
        RED = 2, BLUE = 0, GREEN = -2
    };
    Color c = Color::GREEN;
    out.str("");
    print({.file = &out}, c);
    EXPECT_EQ(out.str(), "Color::GREEN\n");

    enum class Enumeration {
        VAL1, VAL2, VAL3 = 100, VAL4
    };
    Enumeration e = Enumeration::VAL4;
    out.str("");
    print({.file = &out}, e);
    EXPECT_EQ(out.str(), "Enumeration::VAL4\n");
}

TEST(print, pointers) {
    std::ostringstream out;

    int *n = new int;
    *n = 2024;
    out.str("");
    print({.file = &out}, n);
    EXPECT_EQ(out.str(), "2024\n");
    delete n;

    std::unique_ptr<std::vector<int>> pvc(new std::vector<int>({3, 5, 7, 11}));
    out.str("");
    print({.file = &out}, pvc);
    EXPECT_EQ(out.str(), "[3, 5, 7, 11]\n");

}
