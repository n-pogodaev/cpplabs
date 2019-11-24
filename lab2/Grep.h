#pragma once
#include "Worker.h"

class Grep : public Worker {
    std::string word;
public:
    Grep(const std::vector<std::string> &in, std::string wd) : Worker(in), word(std::move(wd)) {}
    ~Grep() override = default;
    void DoWork() override;
};
