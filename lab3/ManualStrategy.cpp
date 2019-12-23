#include "ManualStrategy.h"
#include <iostream>
#include <sstream>

bool GetLetter(std::stringstream &stream, char &let) {
    while (stream.tellg() != -1) {
        stream.get(let);
        if (isspace(let) || let == '-') {
            continue;
        }
        return (let >= 'A' && let <= 'J') || (let >= 'a' && let <= 'j');
    }
    return false;
}

bool GetNumber(std::stringstream &stream, int &num) {
    stream >> num;
    return !(num < 1 || num > 10);
}

void GetField(int &x, int &y) {
    std::string in;
    while (true) {
        getline(std::cin, in);
        std::stringstream stream(in);
        char let;
        if (!GetLetter(stream, let)) {
            std::cout << "Wrong format, try [letter][number], for example A1 or a1" << std::endl;
            continue;
        }
        x = isupper(let) ? let - 'A' + 1 : let - 'a' + 1;
        if (!GetNumber(stream, y)) {
            std::cout << "Wrong format, try [letter][number], for example A1 or a1" << std::endl;
            continue;
        }
        break;
    }
}

void GetRange(int &x1, int &y1, int &x2, int &y2) {
    std::string in;
    while (true) {
        getline(std::cin, in);
        std::stringstream stream(in);
        char let;
        if (!GetLetter(stream, let)) {
            std::cout << "Wrong format, try [letter][number]-[letter][number], for example A1-A3 or a1-a3"
            << std::endl;
            continue;
        }
        x1 = isupper(let) ? let - 'A' + 1 : let - 'a' + 1;
        if (!GetNumber(stream, y1)) {
            std::cout << "Wrong format, try [letter][number]-[letter][number], for example A1-A3 or a1-a3"
            << std::endl;
            continue;
        }
        if (!GetLetter(stream, let)) {
            std::cout << "Wrong format, try [letter][number]-[letter][number], for example A1-A3 or a1-a3"
                      << std::endl;
            continue;
        }
        x2 = isupper(let) ? let - 'A' + 1 : let - 'a' + 1;
        if (!GetNumber(stream, y2)) {
            std::cout << "Wrong format, try [letter][number]-[letter][number], for example A1-A3 or a1-a3"
                      << std::endl;
            continue;
        }
        break;
    }
}

void ManualStrategy::ChooseFieldToShoot(int &x, int &y) {
    std::cout << "Shooting:" << std::endl;
    std::cout << "Please enter the field code" << std::endl;
    GetField(x, y);
}

void ManualStrategy::ChooseFieldsToPlaceShip(int decksNum, int &x1, int &y1, int &x2, int &y2) {
    if (decksNum > 1) {
        std::cout << decksNum << "-decks ship:" << std::endl;
        std::cout << "Please enter field codes range" << std::endl;
        GetRange(x1, y1, x2, y2);
    }
    else {
        std::cout << "1-deck ship:" << std::endl;
        std::cout << "Please enter the field code" << std::endl;
        GetField(x1, y1);
        x2 = x1;
        y2 = y1;
    }
}
