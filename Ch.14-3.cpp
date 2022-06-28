#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// 14 - 3
#include <forward_list>
#include <vector>

// ----- Stopwatch Class --------

struct Stopwatch {
	Stopwatch(std::chrono::nanoseconds& result) :
		result{ result },
		start{ std::chrono::high_resolution_clock::now() }{}
	~Stopwatch() {
		result = std::chrono::high_resolution_clock::now() - start;
	}
private:
	std::chrono::nanoseconds& result;
	const std::chrono::time_point<std::chrono::high_resolution_clock> start;
};

int main() {
	const size_t n = 1'000'000;
	std::chrono::nanoseconds elapsed;
	std::chrono::nanoseconds e1;
	std::chrono::nanoseconds e2;
	{
		Stopwatch stopwatch{ elapsed };
		volatile double result{ 1.23e45 };
		for (double i = 1; i < n; i++) {
			result /= i;
		}

		{
			Stopwatch vec_watch{ e1 };
			std::vector<double> vec(n / 100, 15.2);
			auto itr = vec.begin();
			std::advance(itr, 5'000);
		}
		{
			Stopwatch list_watch{ e2 };
			std::forward_list<double> l(n, 15.2);
			auto itr = l.begin();
			std::advance(itr, 5'000);
		}
	}
	auto time_per_div = elapsed.count() / double{ n };
	printf("Took %gns per division.\n", time_per_div);

	//Vector ends up being faster because the elements are contiguos in memory vs a list
	//When size of container it gets slower

	printf("Took %gns to advance.\n", e1.count());

	printf("Took %gns to advance.\n", e2.count());

}