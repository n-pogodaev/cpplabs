#pragma once
#include "IOWorker.h"

class Writefile : public IOWorker {
public:
    Writefile(const std::string &filename, const std::vector<std::string> &in) : IOWorker(filename, in) {}
    void DoWork() override;
    ~Writefile() override = default;
};
