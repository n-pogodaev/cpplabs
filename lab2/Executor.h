#pragma once
#include "Parser.h"
#include "AllWorkers.h"

class ValidationException: public std::exception {
public:
    ValidationException() : std::exception() {}
    ~ValidationException() override = default;
    const char* what() const override {
        return "workflow logic error";
    }
};

class Executor {
    std::string filename = "in.txt";
public:
    Executor() = default;
    Executor(std::string fname) : filename(std::move(fname)) {}
    ~Executor() = default;
    void Execute();
};
