#pragma once
#include <string>
#include <fstream>
#include <exception>
#include <vector>

class ParsingException: public std::exception {
public:
    ParsingException() : std::exception() {}
    ~ParsingException() override = default;
    const char* what() const noexcept override {
        return "wrong workflow description format in input file";
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
