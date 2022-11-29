#define CATCH_CONFIG_MAIN
#include "catch.hpp"


// ----- 14.2 -----
#include <vector>
#include <numeric>

template<typename T>
concept Integral = std::is_integral<T>::value;


struct intObject {
	intObject(int id) : id{ id } {}
	int id;

	//Same as outside
	static int sum(std::vector<intObject>::iterator begin,
		std::vector<intObject>::iterator end)
	{
		int result = 0;
		while (begin != end) {
			result += begin->id;
			begin++;
		}
		return result;
	}

};

/*int sum(std::vector<intObject>::iterator begin,
		std::vector<intObject>::iterator end) {
	int result = 0;
	while (begin != end) {
		result += begin->id;
		begin++;
	}
	return result;
}*/

int main() {

	std::vector<intObject> objects;
	std::vector<intObject> objects2;
	objects.emplace_back(1);
	objects.emplace_back(2);
	objects.emplace_back(3);
	objects.emplace_back(3);
	objects2.emplace_back(3);
	objects2.emplace_back(3);

	auto sumation = intObject::sum(objects.begin(), objects.end());
	auto sumation2 = intObject::sum(objects2.begin(), objects2.end());
	printf("Sum is : %i", sumation2);

}
