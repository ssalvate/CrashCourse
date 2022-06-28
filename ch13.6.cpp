#define CATCH_CONFIG_MAIN
#include "catch.hpp"


// EXERCISES
// 19-1. Write your own spin lock-based mutex called SpinLock. Expose a lock,
//       a try_lock, and an unlock method. Your class should delete the copy
//       constructor. Try using a std::lock_guard<SpinLock> with an instance
//       of your class.
#include <vector>
#include <initializer_list>

template<typename T>
struct Matrix {
	Matrix(int row, int col, std::initializer_list<T> val) :
		row{ row }, col{ col }, data(row, std::vector<T>{})
	{
		auto itr = val.begin();
		for (size_t r{}; r < row; r++) {
			data[r].assign(itr, itr + col);
			itr += col;
		}
	}

	T& at(size_t row, size_t col) {
		if (row >= this->row || col >= this->col) {
			throw std::out_of_range{ "Index Invalid." };
		}
		return data[row][col];
	}
	const int row, col;
private:
	std::vector<std::vector<T>> data;
};

TEST_CASE("Matrix and std::initializer list") {

	Matrix<int> mat{ 2, 4,
	{1,  2,  3, 4,
	 10, 13, 2, 7 }
	};

	REQUIRE(mat.row == 2);
	REQUIRE(mat.at(1, 0) == 10);
	mat.at(1, 0) = 6;
	REQUIRE(mat.at(1, 0) == 6);
}