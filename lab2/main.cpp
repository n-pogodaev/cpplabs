#include <iostream>
#include "Executor.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "enter file name as parameter" << std::endl;
    }
    try {
        Executor exc(argv[1]);
        exc.Execute();
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
    return 0;
}
