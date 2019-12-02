#include <iostream>
#include "Executor.h"
#include <cstring>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "enter file name as parameter" << std::endl;
        return 0;
    }
    Executor *exc = nullptr;
    if (argc > 2) {
        std::string altIn;
        std::string altOut;
        std::string descFile;
        if (argc == 4 || argc == 6) {
            for (int i = 1; i < argc; ++i) {
                if (std::strcmp(argv[i], "-i") == 0 ) {
                    altIn = argv[++i];
                }
                else if (std::strcmp(argv[i], "-o") == 0) {
                    altOut = argv[++i];
                }
                else if (descFile.empty()) {
                    descFile = argv[i];
                }
                else {
                    std::cerr << "invalid parameters format" << std::endl;
                    return 0;
                }
            }

        }
        else {
            std::cerr << "invalid number of parameters" << std::endl;
            return 0;
        }
        exc = new Executor(descFile, altIn, altOut);
    }
    else {
        exc = new Executor(argv[1]);
    }
    try {
        exc->Execute();
    }
    catch(ParsingException &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch(ValidationException &e) {
        std::cerr << e.what() << std::endl;
        return 2;
    }
    catch(std::fstream::failure &e) {
        std::cerr << "file error" << std::endl;
        return 3;
    }
    catch(...) {
        std::cerr << "unknown error" << std::endl;
        return 4;
    }
    delete exc;
    return 0;
}
