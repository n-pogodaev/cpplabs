#include "gtest/gtest.h"
#include <crtdbg.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtMemState m1, m2, m3;
    int t;
    _CrtMemCheckpoint(&m1);
    t = RUN_ALL_TESTS();
    _CrtMemCheckpoint(&m2);
    if (_CrtMemDifference(&m3, &m1, &m2)) {
        _CrtMemDumpStatistics(&m3);
    }
    _CrtMemDumpAllObjectsSince(&m1);
    return t;
}
