#pragma once
#include "Parser.h"
#include "AllWorkers.h"

class ValidationException: public std::exception {
public:
    ValidationException() : std::exception() {}
    ~ValidationException() override = default;
    const char* what() const noexcept override {
        return "workflow logic error";
    }
};

class Executor {
    std::string filename = "in.txt";
    std::string altIn = "";
    std::string altOut = "";
public:
    Executor() = default;
    Executor(std::string fname) : Executor(std::move(fname), "", "") {}
    Executor(std::string fname, std::string in, std::string out) : filename(std::move(fname)),
                                                                    altIn(std::move(in)) , altOut(std::move(out)) {}
    ~Executor() = default;
    void Execute();
};
