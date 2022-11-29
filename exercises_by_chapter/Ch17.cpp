#define CATCH_CONFIG_MAIN
#include "catch.hpp"

// Ch 17-1

#include <filesystem>
#include <iomanip>
#include <iostream>


void explore(const std::filesystem::directory_entry& directory, std::string_view ext) {

    for (const auto& entry : std::filesystem::recursive_directory_iterator{ directory.path() }) {
        const auto& extension = entry.path().extension().string();
        if (extension == ext) {
            std::cout << entry.path().filename().string() << std::endl;
        }
    }
}


int main(int argc, const char** argv) {
    if (argc != 3) {
        std::cerr << "Usage: treedir PATH";
        return -1;
    }
    const std::filesystem::path sys_path{ argv[1] };
    const std::string ext{ argv[2] };
    std::cout << "-------------------------------------\n";
    std::cout << "Looking for extension : " << ext << " -> " << sys_path << std::endl;
    for (const auto& entry : std::filesystem::directory_iterator{ sys_path }) {
        if (entry.is_directory()) {
            explore(entry, ext);
        }
        else {
            const auto& extension = entry.path().extension().string();
            if (extension == ext) {
                std::cout << entry.path().filename().string() << std::endl;
            }
        }
    }

}