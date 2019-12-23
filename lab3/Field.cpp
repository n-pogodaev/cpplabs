#include "Field.h"

Ship::Ship(unsigned int dNum) : decksNum(dNum) {
    if (decksNum < 1 || decksNum > 4) {
        throw std::invalid_argument("class Ship inizialization error: wrong decksNum value");
    }
}

bool Ship::IsWrecked() {
    for (unsigned int i = 0; i < decksNum; ++i) {
        if (!decks[i].isShot) {
            return false;
        }
    }
    return true;
}

bool IsCoord(int num) {
    return !(num < 1 || num > 10);
}

void Ship::SetCoords(int x1, int y1, int x2, int y2,
                     int x3, int y3, int x4, int y4) {
    if (!IsCoord(x1) || !IsCoord(y1)) {
        throw std::invalid_argument("Ship::SetCoord() error: wrong argument value");
    }
    decks[0].x = x1;
    decks[0].y = y1;
    if (decksNum < 2) return;
    if (!IsCoord(x2) || !IsCoord(y2)) {
        throw std::invalid_argument("Ship::SetCoord() error: wrong argument value");
    }
    decks[1].x = x2;
    decks[1].y = y2;
    if (decksNum < 3) return;
    if (!IsCoord(x3) || !IsCoord(y3)) {
        throw std::invalid_argument("Ship::SetCoord() error: wrong argument value");
    }
    decks[2].x = x3;
    decks[2].y = y3;
    if (decksNum < 4) return;
    if (!IsCoord(x4) || !IsCoord(y4)) {
        throw std::invalid_argument("Ship::SetCoord() error: wrong argument value");
    }
    decks[3].x = x4;
    decks[3].y = y4;
}

bool Ship::DeckByCoords(int x, int y, Deck **deck) {
    if (deck == nullptr) {
        return false;
    }
    for (int i = 0; i < decksNum; ++i) {
        *deck = &decks[i];
        if (decks[i].x == x && decks[i].y == y) {
            return true;
        }
    }
    return false;
};

int GetDecksNumberByShipNumber(int shipNum) {
    if (shipNum < 0 || shipNum > 9) return -1;
    if (shipNum == 0) {
        return 4;
    }
    else if (shipNum <= 2) {
        return 3;
    }
    else if (shipNum <= 5) {
        return 2;
    }
    else {
        return 1;
    }
}

void GetXArea(int x, int &startX, int &endX) {
    if (x == 1) {
        startX = x;
        endX = x + 1;
    }
    else if (x == 10) {
        startX = x - 1;
        endX = x;
    }
    else {
        startX = x - 1;
        endX = x + 1;
    }
}

void GetYArea(int y, int &startY, int &endY) {
    if (y == 1) {
        startY = y;
        endY = y + 1;
    }
    else if (y == 10) {
        startY = y - 1;
        endY = y;
    }
    else {
        startY = y - 1;
        endY = y + 1;
    }
}

bool DoesHaveAdjacentShips(const Field &field, int x, int y) {
    int startX, endX, startY, endY;
    GetXArea(x, startX, endX);
    GetYArea(y, startY, endY);
    for (int i = startY; i <= endY; ++i) {
        for (int j = startX; j <= endX; ++j) {
            if (field.yourField[i - 1][j - 1] == YourFieldState::ship) {
                return true;
            }
        }
    }
    return false;
}
