#pragma once
#include <stdexcept>

enum class EnemyFieldState: char {
    unknown = ' ', miss = 'O', damaged = 'x', wrecked = 'X'
};
enum class YourFieldState: char {
    empty = ' ', ship = '+', shot = 'X', miss = 'O'
};

struct Deck {
    int x;
    int y;
    bool isShot;
};

struct Ship {
    Deck decks[4] = {Deck{0, 0, false}};
    unsigned int decksNum;
    ~Ship() = default;
    explicit Ship(unsigned int dNum);
    void SetCoords(int x1, int y1, int x2 = 1, int y2 = 1,
                   int x3 = 1, int y3 = 1, int x4 = 1, int y4 = 1);
    bool IsWrecked();
    bool DeckByCoords(int x, int y, Deck **);
};

struct Field {
    Ship ships[10] = {Ship(4),
                      Ship(3), Ship(3),
                      Ship(2), Ship(2), Ship(2),
                      Ship(1), Ship(1), Ship(1), Ship(1)};
    YourFieldState yourField [10][10] = {YourFieldState::empty};
    EnemyFieldState enemyField [10][10] = {EnemyFieldState::unknown};
    int shipsCount = 0;
};

int GetDecksNumberByShipNumber(int shipNum);
bool DoesHaveAdjacentShips(const Field &field, int x, int y);
void GetYArea(int y, int &startY, int &endY);
void GetXArea(int x, int &startX, int &endX);