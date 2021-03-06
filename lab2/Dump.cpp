#include "Dump.h"
#include <iostream>

void Dump::DoWork() {
    file.exceptions(std::fstream::failbit | std::fstream::badbit);
    std::string str;
    LinesIntoString(str);
    try {
        if (file.is_open()) {
            file << str;
        }
    }
    catch(std::fstream::failure &e) {
        std::cerr << "unable to write in " << filename << std::endl;
        throw;
    }
    out = std::move(in);
}
