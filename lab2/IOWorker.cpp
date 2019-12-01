#include "IOWorker.h"
#include <iostream>

IOWorker::IOWorker(std::string fname, const std::vector<std::string> &in, std::fstream::openmode om)
        : Worker(in), filename(std::move(fname)) {
    try {
        file.open(filename, om);
    }
    catch(std::fstream::failure &e) {
        std::cerr << "unable to open " << filename << std::endl;
        throw;
    }
}

IOWorker::~IOWorker() {
    try {
        file.close();
    }
    catch(std::fstream::failure &e) {
        std::cerr << "unable to close " << filename << std::endl;
    }
}

void IOWorker::LinesIntoString(std::string &str) {
    for (auto &l : in) {
        str += l;
        str += '\n';
    }
    str.erase(str.end() - 1); // delete last \n
}
