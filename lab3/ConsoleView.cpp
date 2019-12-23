#include "ConsoleView.h"
#include <string>

void ConsoleView::Start() {
    std::cout << "\n============================" << std::endl;
    std::cout << "\tROUND BEGINS\t" << std::endl;
    std::cout << "============================\n" << std::endl;
}

void ConsoleView::Show(Gamer *gm) {
    std::cout << "     A   B   C   D   E   F   G   H   I   J  ";
    std::cout << "        ";
    std::cout << "  A   B   C   D   E   F   G   H   I   J  " << std::endl;
    std::cout << "    --------------------------------------- ";
    std::cout << "        ";
    std::cout << " --------------------------------------- " << std::endl;
    for (int i = 0; i < 10; ++i) {
        if (i < 9) {
            std::cout << i + 1 << "  ";
        }
        else {
            std::cout << 10 << " ";
        }
        for (int j = 0; j < 10; ++j) {
            std::cout << "| " << static_cast<char>(gm->field.yourField[i][j]) << " ";
        }
        std::cout << "|        ";
        for (int j = 0; j < 10; ++j) {
            std::cout << "| " << static_cast<char>(gm->field.enemyField[i][j]) << " ";
        }
        std::cout << "|" << std::endl;
        std::cout << "    --------------------------------------- ";
        std::cout << "        ";
        std::cout << " --------------------------------------- " << std::endl;
    }
    std::cout << std::endl;
}

void ConsoleView::Clear() {
    std::cout << std::string(100, '\n') << std::endl;
}

void ConsoleView::Stop() {
    system("pause");
    std::cout << std::endl;
}

