#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// 15 - 1
#include <cstdio>
#include <unordered_map>
#include <string>


// Check if lowercase of upper
constexpr char pos_A{ 65 }, pos_Z{ 90 }, pos_a{ 97 }, pos_z{ 122 };
constexpr bool within_AZ(char x) { return pos_A <= x && pos_Z >= x; }
constexpr bool within_az(char x) { return pos_a <= x && pos_z >= x; }

struct charHistogram {
    void ingest(std::string_view);
    void print() const;

private:
    std::unordered_map<char, int> count{}; // Track char and its count
};

void charHistogram::ingest(std::string_view x) {
    int n_chars = x.length();
    for (auto c : x) {
        if (within_AZ(c)) count[c]++;
        else if (within_az(c)) count[c - (pos_a - pos_A)]++;//Convert to lowercase
    }
    //printf("%i\n", n_chars);
}

void charHistogram::print() const {
    for (const auto& [key, value] : count) {
        printf("%c : ", key);
        for (int i{}; i < value; i++) {
            printf("*");
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    charHistogram ch;
    printf("Arguments: %d\n", argc);
    for (size_t i{}; i < argc; i++) {
        auto s = std::string{ argv[i] };
        ch.ingest(s);
        printf("%zd: %s\n", i, s.c_str());
    }
    ch.print();
}

