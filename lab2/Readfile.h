#pragma once
#include "IOWorker.h"

class Readfile : public IOWorker {
public:
    Readfile(const std::string &filename) : IOWorker(filename, std::vector<std::string>(), std::fstream::in) {}
    void DoWork() override;
    ~Readfile() override = default;
};
