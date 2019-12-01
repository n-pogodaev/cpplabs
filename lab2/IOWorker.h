#pragma once
#include <fstream>
#include "Worker.h"

class IOWorker : public Worker {
protected:
    std::fstream file;
    std::string filename;
    IOWorker(std::string filename, const std::vector<std::string> &in, std::fstream::openmode om);
    void LinesIntoString(std::string &str);
public:
    ~IOWorker() override;
};
