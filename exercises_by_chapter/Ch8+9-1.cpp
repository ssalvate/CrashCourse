#include <cstdio>

#include "Fibonnacci.h"
#include "PrimeNumber.h"


template <typename Fn, typename In, typename Out>
constexpr Out fold(Fn function, In* Input, size_t Length, Out initial) {
    Out output{ initial };
    for (int i = 0; i < Length; i++) output = function(output, Input[i]);
    return output;
}

int main() {


    // CH 8 
    /*printf("---------Fibonacci Numbers---------\n\n");
    for (const auto i : FibonacciRange{ 5000 }) {
        printf("%d ", i);
    }
    printf("\n\n---------Prime Numbers---------\n\n");
    for (const auto i : PrimeRange{ 5000 }) {
        printf("%d ", i);
    }*/

    /*9-1*/
    /*
    int data[]{100, 200, 300, 400, 500};
    size_t data_len = 5;
    auto test = 200;
    auto sum = fold([](auto x, auto y){return x+y;}, data, data_len, 0);
    auto max = fold([](auto x, auto y){return x > y ? x : y;}, data, data_len, 0);
    auto min = fold([](auto x, auto y) {return x > y ? y : x; }, data, data_len, data[0]);
    auto greater_than = fold([test](auto x, auto y) {return y > test ? ++x : x; }, data, data_len, 0);
    printf("Sum: %d\n", sum);
    printf("Max: %d\n", max);
    printf("Min: %d\n", min);
    printf("Greater than 200: %d\n", greater_than);*/
}