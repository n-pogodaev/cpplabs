#include "Parser.h"
#include <iostream>
#include <sstream>
#include <cctype>

Parser::Parser(const std::string &fname) : filename(fname) {
    try {
        file.open(fname, std::fstream::in);
    }
    catch(std::ifstream::failure &e) {
        std::cerr << "unable to open " << fname << std::endl;
        throw;
    }
}

Parser::~Parser() {
    try {
        file.close();
    }
    catch(std::ifstream::failure &e) {
        std::cerr << "unable to close " << filename << std::endl;
    }
}

std::string ReadFile(std::ifstream &file, const std::string &filename) {
    std::string result;
    file.exceptions(std::ifstream::badbit);
    try {
        if (file.is_open()) {
            while (!file.eof()) {
                result += static_cast<char>(file.get());
            }
        }
    }
    catch(std::ifstream::failure &e) {
        std::cerr << e.what() << "unable to read " << filename << std::endl;
        throw;
    }
    return result;
}

void ParseLine(std::string &&line, std::vector<std::string> &vec) {
    std::stringstream ssm(line);
    std::string str;
    while(getline(ssm, str, ' ')) {
        vec.push_back(std::move(str));
        str = "";
    }
}

bool IsNumber(const std::string &str) {
    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}

void CheckAndClean(std::vector<std::vector<std::string>> &lines) {
    if (lines.size() < 3) {
        throw ParsingException(0);
    }
    // delete "desc"
    if (lines[0].size() != 1 || lines[0][0] != "desc") {
        throw ParsingException(0);
    }
    lines.erase(lines.begin());
    // delete '='
    for (size_t i = 0; i < lines.size() - 2; ++i) {
        if (!IsNumber(lines[i][0]) || lines[i][1] != "=" || (lines[i][3] != "dump" && lines[i][3] != "grep" &&
                                                            lines[i][3] != "readfile" && lines[i][3] != "replace" &&
                                                            lines[i][3] != "sort" && lines[i][3] != "writefile")
                                                         || lines[i].size() > 5 || lines.size() < 3) {
            throw ParsingException(i + 1);
        }
        lines[i].erase(lines[i].begin() + 1);
    }
    // delete csed
    if (lines[lines.size() - 2].size() != 1 || lines[lines.size() - 2][0] != "csed") {
        throw ParsingException(lines.size() - 1);
    }
    lines.erase(lines.end() - 2);
    // check lastLine
    std::vector<std::string> &lastLine = lines[lines.size() - 1];
    if (lastLine.size() % 2 == 0) {
        throw ParsingException(lines.size() + 1);
    }
    for (size_t i = 0; i < lastLine.size(); i+=2) {
        if (!IsNumber(lastLine[i])) {
            throw ParsingException(lines.size() + 1);
        }
    }
    // delete ->
    if (lastLine.size() >= 3) {
        for (size_t i = 1; i < lastLine.size(); i += 2) {
            if (lastLine[i] != "->") {
                throw ParsingException(lines.size() - 1);
            }
            lastLine.erase(lastLine.begin() + i);
        }
    }
}

void Parser::Parse() {
    std::stringstream ssm(ReadFile(file, filename));
    std::string nextLine;
    while (ssm) {
        std::getline(ssm, nextLine);
        std::vector<std::string> nextLineVec;
        ParseLine(std::move(nextLine), nextLineVec);
        lines.push_back(std::move(nextLineVec));
        nextLine = "";
    }
    try {
        CheckAndClean(lines);
    }
    catch (ParsingException &e) {
        throw;
    }
}
