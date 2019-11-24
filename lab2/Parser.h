#pragma once
#include <string>
#include <fstream>
#include <exception>
#include <vector>

class ParsingException: public std::exception {
    size_t line = 0;
public:
    ParsingException(size_t lineNum) : std::exception(), line(lineNum) {}
    ~ParsingException() override = default;
    const char* what() const override {
        return (std::to_string(line) + std::string(": wrong workflow description format in input file")).c_str();
    }
};

class Parser {
    std::ifstream file;
    std::string filename;
    std::vector<std::vector<std::string>> lines;
public:
    Parser(const std::string &fname);
    ~Parser();
    void Parse();
    std::vector<std::vector<std::string>> GetParsedVec() { return lines; }
};
