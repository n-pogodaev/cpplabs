#pragma once
#include <fstream>
#include "Worker.h"

class IOWorker : public Worker {
protected:
    std::fstream file;
    std::string filename;
    IOWorker(std::string filename, const std::vector<std::string> &in);
    IOWorker(std::string filename) : IOWorker(std::move(filename), std::vector<std::string>()) {}
    void LinesIntoString(std::string &str);
public:
    ~IOWorker() override;
};
