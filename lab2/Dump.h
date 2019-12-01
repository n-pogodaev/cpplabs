#pragma once
#include "IOWorker.h"

class Dump : public IOWorker {
public:
    Dump(const std::string &filename, const std::vector<std::string> &in) : IOWorker(filename, in, std::fstream::out) {}
    void DoWork() override;
    ~Dump() override = default;
};
