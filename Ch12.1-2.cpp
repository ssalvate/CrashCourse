#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstdio>
#include <stdexcept>
#include <optional>

template <typename To, typename From>
std::optional<To> narrow_cast(From value) {
    const auto converted = static_cast<To>(value);
    const auto backwards = static_cast<From>(converted);
    if (value != backwards) return std::nullopt;
    return converted;
}


TEST_CASE("Narrow_cast") {

    SECTION("Working narrow cast") {
        int perfect{ 496 };
        const auto short_optional = narrow_cast<short>(perfect);
        REQUIRE(short_optional.value() == 496);
    }
    SECTION("Cast caused narrowing") {
        int cyclic{ 142857 };
        const auto short_optional = narrow_cast<short>(cyclic);
        REQUIRE_FALSE(short_optional.has_value());
    }

}

// 12-2
/*

#include <random>
#include <cstdio>

int main() {

    const int password_len{ 4 };

    std::random_device rd_engine{};

    const char characters[]{'a', 'b', '4', '12', 'x', 'z'};
    const auto size{ sizeof(characters) };

    std::uniform_int_distribution<int> distribution(0, size - 1);

    printf("Your password is: ");
    for (size_t i = 0; i < password_len; i++) printf("%c", characters[distribution(rd_engine)]);
    printf("\n");
}

*/

/*
int main() {
    int perfect{ 496 };
    const auto perfect_short = narrow_cast<short>(perfect);
    printf("perfect_short: %d\n", perfect_short);
    try {
        int cyclic{ 142857 };
        const auto cyclic_short = narrow_cast<short>(cyclic);
        printf("cyclic_short: %d\n", cyclic_short);
    }
    catch (const std::runtime_error& e) {
        printf("Exception: %s\n", e.what());
    }
}*/
