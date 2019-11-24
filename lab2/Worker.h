#pragma once
#include <string>
#include <utility>
#include <vector>
#include <sstream>

class Worker {
protected:
    std::vector<std::string> in = std::vector<std::string>();
    std::vector<std::string> out = std::vector<std::string>();
    Worker() = default;
    Worker(std::vector<std::string> lines) : in(std::move(lines)) {}
public:
    virtual ~Worker() = default;
    virtual void DoWork() = 0;
    std::vector<std::string> GetLines() const { return out; }
};
