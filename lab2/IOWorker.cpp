#include "IOWorker.h"
#include <iostream>

IOWorker::IOWorker(std::string fname, const std::vector<std::string> &in) : Worker(in), filename(std::move(fname)) {
    try {
        file.open(filename, std::fstream::in | std::fstream::app);
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
    }
}
