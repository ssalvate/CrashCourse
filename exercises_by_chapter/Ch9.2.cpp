#include <cstdint>
#include <cstdio>
#include <unordered_map>

struct charHistogram {
    void ingest(const int index, const char* x);
    void print() const;

private:
    std::unordered_map<int, int> count{}; // Track argument index and argument char length
};

void charHistogram::ingest(const int index, const char* x) {
    int n_chars = strlen(x);
    count[index] = n_chars;
    //printf("%i\n", n_chars);
}

void charHistogram::print() const {
    for (const auto& [key, value] : count) {
        printf("Arg %i: ", key);
        for (int i{}; i < value; i++) {
            printf("*");
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    charHistogram ch;
    printf("Arguments: %d\n", argc);
    for (size_t i{}; i < argc; i++) {
        ch.ingest(i, argv[i]);
        printf("%zd: %s\n", i, argv[i]);
    }
    ch.print();
}
