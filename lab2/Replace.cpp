#include "Replace.h"

void Replace::DoWork() {
    out = std::move(in);
    for (auto &l : out) {
        size_t pos = l.find(bef);
        while (pos != std::string::npos) {
            l.replace(pos, bef.size(), aft);
            pos = l.find(bef, pos + aft.size());
        }
    }
}
