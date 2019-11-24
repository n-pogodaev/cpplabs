#include "Readfile.h"
#include <iostream>

void ParseStringToLines(std::string &&str, std::vector<std::string> &lines) {
    std::stringstream ssm(str);
    std::string nextLine;
    while (getline(ssm, nextLine)) {
        nextLine += '\n'; // add '\n' in every line
        lines.push_back(std::move(nextLine));
        nextLine = "";
    }
    std::string &lastLine = lines[lines.size() - 1];
    lastLine.erase(lastLine.end() - 1); // delete last '\n'
}

void Readfile::DoWork() {
    file.exceptions(std::fstream::badbit);
    std::string text;
    try {
        if (file.is_open()) {
            while (!file.eof()) {
                text += static_cast<char>(file.get());
            }
        }
    }
    catch(std::fstream::failure &e) {
        std::cerr << "unable to read " << filename << std::endl;
        throw;
    }
    ParseStringToLines(std::move(text), out);
}
