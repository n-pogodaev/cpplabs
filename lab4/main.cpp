#include "CSVParser.h"

int main() {
    std::ifstream file("test.csv");
    CSVParser<int, std::string, std::string> parser(file, 0, '\n', ',', '"');
    for (auto &rs : parser) {
        std::cout << rs << std::endl;
    }
}
