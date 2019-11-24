#pragma once
#include "Worker.h"

class Replace : public Worker {
    std::string bef;
    std::string aft;
public:
    Replace(const std::vector<std::string> &in,
            std::string b, std::string a) :
            Worker(in), bef(std::move(b)), aft(std::move(a)) {}
    ~Replace() override = default;
    void DoWork() override;
};
