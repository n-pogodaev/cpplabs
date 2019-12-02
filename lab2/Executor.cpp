#include "Executor.h"
#include <algorithm>
#include <unordered_map>

struct Block {
    std::string name;
    std::string firstParameter;
    std::string secParameter;
};

void CastParsedVec(const std::vector<std::vector<std::string>> &parsedVec,
        std::unordered_multimap<size_t, Block> &desc, std::vector<size_t> &queue) {
    for (size_t i = 0; i < parsedVec.size() - 2; ++i) {
        Block b;
        b.name = parsedVec[i][1];
        if (parsedVec[i].size() >= 3) {
            b.firstParameter = parsedVec[i][2];
        }
        else {
            b.firstParameter = "";
        }
        if (parsedVec[i].size() == 4) {
            b.secParameter = parsedVec[i][3];
        }
        else {
            b.secParameter = "";
        }
        desc.insert(std::make_pair(stol(parsedVec[i][0]), b));
    }
    for (const auto &i : parsedVec[parsedVec.size() - 2]) {
        queue.push_back(std::stol(i));
    }
}

bool ValidateBlocksDescription(const std::unordered_multimap<size_t, Block> &desc) {
    for (const auto &b : desc) {
        if (desc.count(b.first) > 1) {
            return false;
        }
        if ((b.second.name == "readfile" || b.second.name == "writefile" || b.second.name == "dump" || b.second.name == "grep") &&
                (b.second.firstParameter.empty() || !b.second.secParameter.empty()) ) {
            return false;
        }
        if (b.second.name == "sort" && !b.second.firstParameter.empty()) {
            return false;
        }
        if (b.second.name == "replace" && b.second.secParameter.empty()) {
            return false;
        }
    }
    return true;
}

bool ValidateExecQueue(const std::vector<size_t> &execQueue, const std::unordered_multimap<size_t, Block> &desc,
                        std::string &altIn, std::string &altOut) {
    if (!execQueue.empty()) {
        if (desc.count(execQueue[0]) != 1 || desc.count(execQueue[execQueue.size() - 1]) != 1 ||
            (desc.find(execQueue[0])->second.name != "readfile" && altIn.empty()) ||
            (desc.find(execQueue[execQueue.size() - 1])->second.name != "writefile" && altOut.empty())) {
            return false;
        }
        if (desc.find(execQueue[0])->second.name == "readfile") {
            altIn = "";
        }
        if (desc.find(execQueue[execQueue.size() - 1])->second.name == "writefile") {
            altOut = "";
        }
        for (size_t i = 1; i < execQueue.size() - 1; ++i) {
            if (desc.count(execQueue[i]) != 1 ||
                desc.find(execQueue[i])->second.name == "readfile" ||
                desc.find(execQueue[i])->second.name == "writefile") {
                return false;
            }
        }
    }
    return true;
}

void ExecBlocks(const std::unordered_multimap<size_t, Block> &desc, const std::vector<size_t> &queue,
                const std::string &altIn, const std::string &altOut) {
    std::vector<std::string> boundLines;
    if (!altIn.empty()) {
        Readfile rf(altIn);
        rf.DoWork();
        boundLines = std::move(rf.GetLines());
    }
    for(const auto &i : queue) {
        const Block b = desc.find(i)->second;
        std::string commandName = b.name;
        Worker * block = nullptr;
        if (commandName == "readfile") {
            block = new Readfile(b.firstParameter);
        }
        else if (commandName == "writefile") {
            block = new Writefile(b.firstParameter, boundLines);
        }
        else if (commandName == "dump") {
            block = new Dump(b.firstParameter, boundLines);
        }
        else if (commandName == "grep") {
            block = new Grep(boundLines, b.firstParameter);
        }
        else if (commandName == "sort") {
            block = new Sort(boundLines);
        }
        else {
            block = new Replace(boundLines, b.firstParameter, b.secParameter);
        }
        block->DoWork();
        boundLines = std::move(block->GetLines());
        delete block;
    }
    if (!altOut.empty()) {
        Writefile wf(altOut, boundLines);
        wf.DoWork();
    }
}

void Executor::Execute() {
    Parser psr(filename);
    try {
        psr.Parse();
    }
    catch(ParsingException &e) {
        throw;
    }
    std::vector<size_t> execQueue;
    std::unordered_multimap<size_t, Block> desc;
    CastParsedVec(psr.GetParsedVec(), desc, execQueue);
    std::string in = altIn;
    std::string out = altOut;
    if (!ValidateBlocksDescription(desc) || !ValidateExecQueue(execQueue, desc, in, out)) {
        throw ValidationException();
    }
    try {
        ExecBlocks(desc, execQueue, in, out);
    }
    catch(std::fstream::failure &e) {
        throw;
    }
}
