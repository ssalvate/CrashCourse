#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <vector>
#include <array>

TEST_CASE("Chapter 13 Exercises") {

	SECTION("13-1") {
		printf("-------- 13-1 -------- \n\n");
		std::vector<unsigned long> u_longs;
		printf("Size: %lu\n", u_longs.size());
		printf("Capacity: %lu\n", u_longs.capacity());

		u_longs.reserve(10);
		printf("Capacity after reserve(10): %lu\n", u_longs.capacity());

		unsigned long n1 = 0, n2 = 1, n3, i, number = 20;
		u_longs.push_back(n1);
		u_longs.push_back(n2);
		printf("%i %i ", n1, n2); //printing 0 and 1    

		for (i = 2; i < number; ++i) //loop starts from 2 because 0 and 1 are already printed    
		{
			n3 = n1 + n2;
			u_longs.push_back(n3);
			printf("%i ", n3);
			n1 = n2;
			n2 = n3;
		}
		printf("\n");
		printf("Size after fib: %lu\n", u_longs.size());
		printf("Capacity after fib: %lu\n", u_longs.capacity());

		for (auto elem : u_longs)printf("% lu ", elem);
		printf("\n\n\n");
	}

	SECTION("13-2") {
		printf("-------- 13-2 -------- \n\n");
		printf("---- 2.9 -------- \n");

		std::array<int, 4> arr{ 1, 2, 3, 4 };
		printf("The third element is %d.\n", std::get<2>(arr));
		std::get<2>(arr) = 100;
		printf("The third element after  %d.\n", std::get<2>(arr));
		REQUIRE(std::get<2>(arr) == 100);

		printf("\n---- 2.10 -------- \n");

		unsigned long maximum = 0;
		std::array<unsigned long, 5 > values{ 10, 50, 20, 40, 0 };
		for (size_t i = 0; i < 5; i++) {
			if (values.at(i) > maximum)
				maximum = values.at(i);
		}
		REQUIRE(maximum == Approx(50));
		printf("The maximum value is %lu. \n", maximum);

		printf("\n---- 2.11 -------- \n");

		unsigned long max = 0;
		std::array<unsigned long, 5> vals{ 10, 50, 20, 40, 0 };
		for (unsigned long value : vals) {
			if (value > max)
				max = value;
		}
		REQUIRE(max == Approx(50));
		printf("The maximum value is %lu. \n", max);

	}
}