
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/*
	14.1
*/
#include <iterator>

TEST_CASE("next returns iterators at given offsets") {



	SECTION("14-1") {

		std::vector<unsigned char> mission{
			0x9e, 0xc4, 0xc1, 0x29,
			0x49, 0xa4, 0xf3, 0x14,
			0x74, 0xf2, 0x99, 0x05,
			0x8c, 0xe2, 0xb2, 0x2a
		};

		auto itr1 = mission.begin();
		std::advance(itr1, 4);
		REQUIRE(*itr1 == 0x49);

		//Using next
		auto itr2 = std::next(itr1);
		REQUIRE(*itr2 == 0xa4);

		auto itr3 = std::next(itr1, 4);
		REQUIRE(*itr3 == 0x74);

		REQUIRE(*itr1 == 0x49);

		//Using prev
		auto itr4 = mission.end();
		std::advance(itr4, -2);
		REQUIRE(*itr4 == 0xb2);

		auto itr5 = std::prev(itr4);
		REQUIRE(*itr5 == 0xe2);
	}



}