#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <set>

struct CStringComparator {

	bool operator()(const char* c_1, const char* c_2) const {
		size_t max_index = std::min(strlen(c_1), strlen(c_2));
		for (size_t i = 0; i < max_index; i++)
		{
			if (c_1[i] < c_2[i]) return true;
			else if (c_1[i] > c_2[i]) return false;
		}
		return strlen(c_1) < strlen(c_2);
	}

};

int main(int argc, const char* argv[]) {
	// NOTE : argv starts at [1], [0] is the command running the program
	for (int i = 0; i < argc; ++i)
		printf("%s, ", argv[i]);

	printf("\n");

	//Initialize a set with range, remember default array is a pointer
	std::set<const char*, CStringComparator> arguments(argv + 1, argv + argc);
	for (auto elem : arguments) printf("%s\n", elem);

}