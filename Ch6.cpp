#include <cstdio>
#include <utility>
#include <unordered_map>

struct Tracer {
    Tracer(const char* name)
        : name{ name } {
        printf("%s constructed.\n", name);
    }
    ~Tracer() {
        printf("%s destructed.\n", name);
    }

private:
    const char* const name;
};

template<typename T>
concept integral = std::is_integral<T>::value;

// Accepts an array, not a pointer to an array
template <typename T, size_t Length>
T mean(T(&arr)[Length]) {
    T result{};
    for (size_t i{}; i < Length; i++) {
        result += arr[i];
    }
    return result / Length;
}

template<integral T>
T mode(const T* values, size_t length) {
    // Insert all elements in hash.

    std::unordered_map<int, int> hash;
    for (size_t i{}; i < length; i++)
        hash[values[i]]++;

    // find the max frequency
    int max_count = 0, res = -1;
    for (auto i : hash) {
        if (max_count < i.second) {
            res = i.first;
            max_count = i.second;
        }
    }

    return res;
}

int main() {
    int arr[]{ 1,1,1,1,2,3,4,4,5,5,5 };
    int arr1[]{ 1,2,3,4,5 };
    //double arr[]{ 1,1,2,3,4,4,5,5,5 }; Does not compile
    printf("Mode of array is: %d\n", mode(arr, 11));
    printf("Mean of array is: %d\n", mean(arr1));
}
