#include "Sort.h"
#include <algorithm>

void Sort::DoWork() {
    out = std::move(in);
    std::sort(out.begin(), out.end());
    std::string l;
}
