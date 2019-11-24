#pragma once
#include "Worker.h"

class Sort : public Worker {
public:
    Sort(const std::vector<std::string> &in) : Worker(in) {}
    ~Sort() override = default;
    void DoWork() override;
};
