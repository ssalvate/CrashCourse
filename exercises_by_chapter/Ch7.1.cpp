#include <cstdio>
#include <stdexcept>
#include <stdint.h>
#include <cmath>

template<typename T>
concept integral = std::is_integral<T>::value;

//Takes in a char array up to [8]
struct UnsignedBigInt {

	template<size_t N>
	UnsignedBigInt(char(&input)[N]) {
		int len = sizeof(input) / sizeof(char);

		for (int i{}; i < len - 1; i++) {
			uint8_t as_int = input[i] - '0';
			number[7 - i] = as_int;
		}
	}

	template<size_t N>
	UnsignedBigInt(uint8_t(&arr)[N]) {
		for (size_t i{}; i < N; i++) {
			number[i] = arr[i];
		}
	}

	template<integral T>
	UnsignedBigInt operator+(T value) {

		uint8_t value_arr[8]{};
		//Integral(i.e int->array)
		for (int i{ 7 }; i >= 0; i--) {
			value_arr[7 - i] = value % 10;
			//printf("Value arr[%i] = %i\n", i, value_arr[i]);
			value /= 10;
		}

		uint8_t result[8]{};
		int rem = false;
		for (size_t i{ 0 }; i < 8; i++) {
			auto val = rem ? this->number[i] + value_arr[i] + 1 : number[i] + value_arr[i];
			if (val >= 10) {
				rem = true;
				result[i] = val - 10;
			}
			else {
				result[i] = val;
				rem = false;
			}
		}
		//if still true mean last value went into [9]
		if (rem) {
			throw std::runtime_error{ " Overflow! " };
		}

		return UnsignedBigInt{ result };
	}


	UnsignedBigInt operator+(UnsignedBigInt& other) {
		uint8_t result[8]{};
		int rem = false;
		for (size_t i{ 0 }; i < 8; i++) {
			auto val = rem ? this->number[i] + other.number[i] + 1 : number[i] + other.number[i];
			if (val >= 10) {
				rem = true;
				result[i] = val - 10;
			}
			else {
				result[i] = val;
				rem = false;
			}
		}
		//if still true mean last value went into [9]
		if (rem) {
			throw std::runtime_error{ " Overflow! " };
		}

		return UnsignedBigInt{ result };
	}

	//Simple conversion to int
	operator int() const {
		int result{ 0 };
		for (uint8_t i{}; i < 8; i++) {
			result = result + (this->number[i] * static_cast<int>(pow(10, i)));
		}
		if (result > INT_MAX) {
			printf("narrowing occured/n");
		}
		return result;
	}

	void print() {
		bool non_zero = false;
		for (int i{ 7 }; i >= 0; i--) {
			if (this->number[i] > 0)non_zero = true;
			if (non_zero)printf(" %i ", this->number[i]);
		}
		printf("\n");
	}

	uint8_t number[8]{};
};

int main() {
	char a[]{ "00000092" };
	char b[]{ "00000900" };
	UnsignedBigInt big1{ a };
	UnsignedBigInt big2{ b };
	big1.print();
	big2.print();

	auto casted = static_cast<int>(big1);
	printf("Casted to integer = %i\n", casted);
	try {
		//auto r1 = big1 + big2;
		//r1.print();
		auto r2 = big2 + 30000000;
		r2.print();
	}
	catch (const std::runtime_error& e) {
		printf("Exeption: %s\n", e.what());
	}
}
