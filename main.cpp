#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <algorithm>
#include <vector>
#include <utility>

int solution(std::vector<int>& A) {
    //Sort Array [-1,0,2,3,8]
    if (A.size() == 2) return 0;
    std::vector<int> C{ A };
    std::sort(C.begin(), C.end());

    //prev value = A[0]

    std::pair<int, int> biggest_gap{};
    //loop thru array A[i]
    int prev = C[0];
    for (size_t i{ 1 }; i < C.size(); i++) {
        if (C[i] - 1 != prev) {
            if (C[i] - prev > biggest_gap.second) {
                biggest_gap.first = C[i];
                biggest_gap.second = C[i] - prev;
            }
        }
        prev = C[i];
    }
    //if  A[i] - 1 !== prev: Difference if Bigger than last diff. Also Store map<location(i.e.8), gap size>
    if (biggest_gap.second % 2 == 0)
        return biggest_gap.first - biggest_gap.second / 2;
    else
        return biggest_gap.first - biggest_gap.second - 1;
    //After loop take location and subtract gap size/2 -1 if odd
    //This is location
    //Need something extra to deal with neg?

}

int main() {
    std::vector<int> a{ 1, 3, 6, 4, 1, 2 };
    std::vector<bool> present(a.size() + 1, false); // +1 cause 1 missing
    printf("present size is : %i\n", present.size());
    std::vector<int> test{ 5,5 };
    int result = solution(test);
    printf("Result =  %i", test.size());

}