#define CATCH_CONFIG_MAIN
#include "catch.hpp"


// --- 15-2  & 15-3 ----
#include <string>
#include <string_view>

bool isPaliondrome(std::string_view sv) {
    auto f_iter = sv.begin();
    auto r_iter = sv.rbegin();
    unsigned int n_checks = sv.length() / 2;
    while (n_checks--) {
        if (*f_iter != *r_iter) return false;
        f_iter++;
        r_iter++;
    }

    return true;
}

int countVowels(std::string_view sv) {
    const std::string v{ "aeiou" };
    unsigned int result{};
    unsigned int index{};
    while (index < sv.length()) {
        auto i = sv.find_first_of(v, index);
        index = i + 1;
        result++;
    }
    return result;
}

int main(int argc, char** argv) {
    if (argc != 2) printf("Please pass one argument.");
    else {
        auto s = std::string{ argv[1] };
        bool result = isPaliondrome(s);
        int count = countVowels(s);
        printf("Is %s a palindrome? %s\n", s.c_str(), result ? "true" : "false");
        printf("Vowels in %s : %i\n", s.c_str(), count);
    }
}