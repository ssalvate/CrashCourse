#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <chrono>
#include <cstdio>
#include <random>
#include <map>
#include <unordered_map>


// Baseline : 142724 s.
long fib_sum(size_t n) {
	if (n < 3) return n;

	std::vector<long> longs;

	longs.reserve(n);

	unsigned long n1 = 0, n2 = 1, n3, i;
	longs.push_back(n1);
	longs.push_back(n2);

	for (i = 2; i < n; ++i)
	{
		n3 = n1 + n2;
		longs.push_back(n3);
		n1 = n2;
		n2 = n3;
	}

	long sum = 0;

	for (auto elem : longs)sum += elem;
	return sum;
}

long random() {
	static std::mt19937_64 mt_engine{ 102787 };
	static std::uniform_int_distribution<long> int_d{ 1000, 2000 };
	return int_d(mt_engine);
}

struct Stopwatch {
	Stopwatch(std::chrono::nanoseconds& result) : result{ result },
		start{ std::chrono::system_clock::now() } {}
	~Stopwatch() {
		result = std::chrono::system_clock::now() - start;
	}

private:
	std::chrono::nanoseconds& result;
	const std::chrono::time_point<std::chrono::system_clock> start;
};


// Map: 1028.13 s.
// Unordered : 398.669 s.
long cached_fib_sum(const size_t& n) {
	//static std::map<long, long> cache;
	static std::unordered_map<long, long> cache;

	if (!cache.contains(n)) cache[n] = fib_sum(n);
	else return cache.at(n);
}

int main() {
	size_t samples{ 1'000'000 };
	std::chrono::nanoseconds elapsed;

	{
		Stopwatch stopwatch(elapsed);
		volatile double answer;
		while (samples--) {
			//answer = fib_sum(random());
			answer = cached_fib_sum(random());
		}
	}

	printf("Elapsed: %g s.\n", elapsed.count() / 1'000'000.);
}