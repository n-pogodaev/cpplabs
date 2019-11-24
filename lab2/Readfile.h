#pragma once
#include "IOWorker.h"

class Readfile : public IOWorker {
public:
    Readfile(const std::string &filename) : IOWorker(filename) {}
    void DoWork() override;
    ~Readfile() override = default;
};
