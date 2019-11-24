#include "Grep.h"

void Grep::DoWork()  {
    for (const auto &l : in) {
        if (l.find(word) != std::string::npos) {
            out.push_back(l);
        }
    }
}
