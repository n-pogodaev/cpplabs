#include "OptimalStrategy.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

void GetPattern(int pattern, Field &field) {
    if (pattern == 0) {
        field.ships[0].SetCoords(1, 1, 1, 2, 1, 3, 1, 4);
        field.ships[1].SetCoords(3, 1, 3, 2, 3, 3);
        field.ships[2].SetCoords(3, 5, 3, 6, 3, 7);
        field.ships[3].SetCoords(1, 6, 1, 7);
        field.ships[4].SetCoords(1, 9, 1, 10);
        field.ships[5].SetCoords(3, 9, 3, 10);
    }
    else if (pattern == 1) {
        field.ships[0].SetCoords(1, 1, 1, 2, 1, 3, 1, 4);
        field.ships[1].SetCoords(3, 1, 4, 1, 5, 1);
        field.ships[2].SetCoords(1, 6, 1, 7, 1, 8);
        field.ships[3].SetCoords(1, 10, 2, 10);
        field.ships[4].SetCoords(7, 1, 8, 1);
        field.ships[5].SetCoords(10, 1, 10, 2);
    }
    else { // pattern == 2
        field.ships[0].SetCoords(1, 1, 1, 2, 1, 3, 1, 4);
        field.ships[1].SetCoords(10, 1, 10, 2, 10, 3);
        field.ships[2].SetCoords(10, 8, 10, 9, 10, 10);
        field.ships[3].SetCoords(10, 5, 10, 6);
        field.ships[4].SetCoords(1, 6, 1, 7);
        field.ships[5].SetCoords(1, 9, 1, 10);
    }
}

void DoRotation(int rotation, Field &field) {
    for (int i = 0; i < rotation; ++i) {
        for (auto & ship : field.ships) {
            auto decksNum = ship.decksNum;
            for (int k = 0; k < decksNum; ++k) {
                std::swap(ship.decks[k].x, ship.decks[k].y);
                ship.decks[k].x = 11 - ship.decks[k].x;
            }
        }
    }
}

void DoReflection(int reflection, Field &field) {
    for (auto & ship : field.ships) {
        auto decksNum = ship.decksNum;
        for (int k = 0; k < decksNum; ++k) {
            if (reflection == 0) {
                ship.decks[k].x = 11 - ship.decks[k].x;
            }
            else if (reflection == 1) {
                ship.decks[k].y = 11 - ship.decks[k].y;
            }
            else {
                return;
            }
        }
    }
}

void DrawShips(Field &field) {
    for (auto &ship : field.ships) {
        for (int i = 0; i < ship.decksNum; ++i) {
            int x = ship.decks[i].x;
            int y = ship.decks[i].y;
            if (x != 0 && y != 0) {
                field.yourField[y - 1][x - 1] = YourFieldState::ship;
            }
        }
    }
}

void PutOneDeckShips(Field &field) {
    int freeFields[100];
    srand(time(nullptr));
    for (int k = 0; k < 4; ++k) {
        int freeFieldsCount = 0;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (!DoesHaveAdjacentShips(field, j + 1, i + 1)) {
                    freeFields[freeFieldsCount] = i * 10 + j;
                    ++freeFieldsCount;
                }
            }
        }
        int pickedFieldNum = (rand() % freeFieldsCount) + 1;
        auto &x = field.ships[k + 6].decks[0].x;
        auto &y = field.ships[k + 6].decks[0].y;
        x = freeFields[pickedFieldNum - 1] % 10 + 1;
        y = freeFields[pickedFieldNum - 1] / 10 + 1;
        field.yourField[y - 1][x - 1] = YourFieldState::ship;
    }
}

OptimalStrategy::OptimalStrategy(const Field &f) : Strategy(f) {
    for (auto & i : optimalField.yourField) {
        for (auto & j : i) {
            j = YourFieldState::empty;
        }
    }
    srand(time(nullptr));
    int pattern = rand() % 3;
    int rotation = rand() % 4;
    int reflection = rand() % 3;
    GetPattern(pattern, optimalField);
    DoRotation(rotation, optimalField);
    DoReflection(reflection, optimalField);
    DrawShips(optimalField);
    PutOneDeckShips(optimalField);
}

void OptimalStrategy::ChooseFieldsToPlaceShip(int decksNum, int &x1, int &y1, int &x2, int &y2) {
    for (int i = 0; i < 10; ++i) {
        const auto &ship = field.ships[i];
        if (ship.decksNum == decksNum && ship.decks[0].x == 0 && ship.decks[0].y == 0) {
            x1 = optimalField.ships[i].decks[0].x;
            y1 = optimalField.ships[i].decks[0].y;
            x2 = optimalField.ships[i].decks[decksNum - 1].x;
            y2 = optimalField.ships[i].decks[decksNum - 1].y;
            return;
        }
    }
}

struct Coord {
    Coord(int ix, int iy) : x(ix), y(iy) {}
    int x;
    int y;
};

Coord GetOptimalShootField(int num) {
    static const Coord optimalShootFields[50] = {Coord(1,8), Coord(2,7), Coord(3,6), Coord(4,5),
                                                 Coord(5,4), Coord(6,3), Coord(7,2), Coord(8,1),
                                                 Coord(3,10), Coord(4,9), Coord(5,8), Coord(6,7),
                                                 Coord(7,6), Coord(8,5), Coord(9,4), Coord(10,3),
                                                 Coord(1,4), Coord(2,3), Coord(3,2), Coord(4,1),
                                                 Coord(7,10), Coord(8,9), Coord(9,8), Coord(10,7),
                                                 Coord(1,10), Coord(2,9), Coord(3,8), Coord(4,7),
                                                 Coord(5,6), Coord(6,5), Coord(7,4), Coord(8,3),
                                                 Coord(9,2), Coord(10,1), Coord(1,6), Coord(2,5),
                                                 Coord(3,4), Coord(4,3), Coord(5,2), Coord(6,1),
                                                 Coord(5,10), Coord(6,9), Coord(7,8), Coord(8,7),
                                                 Coord(9,6), Coord(10,5), Coord(1,2), Coord(2,1),
                                                 Coord(9,10), Coord(10,9)};
    if (num < 0 || num >= 50) {
        return {0,0};
    }
    return optimalShootFields[num];
}

bool IsPointlessToShoot(const Field &field, int x, int y) {
    if (field.enemyField[y - 1][x - 1] == EnemyFieldState::miss ||
    field.enemyField[y - 1][x - 1] == EnemyFieldState::damaged) {
        return true;
    }
    int startX, endX, startY, endY;
    GetXArea(x, startX, endX);
    GetYArea(y, startY, endY);
    for (int i = startY; i <= endY; ++i) {
        for (int j = startX; j <= endX; ++j) {
            if (field.enemyField[i - 1][j - 1] == EnemyFieldState::wrecked) {
                return true;
            }
        }
    }
    return false;
}

void SeekForOneDeckShips(const Field &field, int &x, int &y) {
    int notShotFields[50];
    srand(time(nullptr));
    int notShotFieldsCount = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (!IsPointlessToShoot(field, j + 1, i + 1)) {
                notShotFields[notShotFieldsCount] = i * 10 + j;
                ++notShotFieldsCount;
            }
        }
    }
    int pickedFieldNum = (rand() % notShotFieldsCount) + 1;
    x = notShotFields[pickedFieldNum - 1] % 10 + 1;
    y = notShotFields[pickedFieldNum - 1] / 10 + 1;
}

void Scout(const Field &field, int &x, int &y) {
    for (int i = 0; i < 50; ++i) {
        Coord c = GetOptimalShootField(i);
        if (!IsPointlessToShoot(field, c.x, c.y)) {
            x = c.x;
            y = c.y;
            return;
        }
    }
    SeekForOneDeckShips(field, x, y);
}

void Finish(const Field &field, int &x, int &y) {
    int fx = 0, fy = 0;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (field.enemyField[i][j] == EnemyFieldState::damaged) {
                fx = j + 1;
                fy = i + 1;
                goto end;
            }
        }
    }
    end:
    if (fx == 0 || fy == 0) {
        return;
    }
    if (fx < 10 && field.enemyField[fy - 1][fx + 1 - 1] == EnemyFieldState::damaged) {
        if (fx > 1 && !IsPointlessToShoot(field, fx - 1, fy)) {
            x = fx - 1;
            y = fy;
        }
        else {
            while (field.enemyField[fy - 1][fx - 1] == EnemyFieldState::damaged) {
                ++fx;
            }
            x = fx;
            y = fy;
        }
    }
    else if (fy < 10 && field.enemyField[fy + 1 - 1][fx - 1] == EnemyFieldState::damaged) {
        if (fy > 1 && !IsPointlessToShoot(field, fx, fy - 1)) {
            x = fx;
            y = fy - 1;
        }
        else {
            while (field.enemyField[fy - 1][fx - 1] == EnemyFieldState::damaged) {
                ++fy;
            }
            x = fx;
            y = fy;
        }
    }
    else {
        if (fy > 1 && !IsPointlessToShoot(field, fx, fy - 1)) {
            x = fx;
            y = fy - 1;
        }
        else if (fx < 10 && !IsPointlessToShoot(field, fx + 1, fy)) {
            x = fx + 1;
            y = fy;
        }
        else if (fy < 10 && !IsPointlessToShoot(field, fx, fy + 1)) {
            x = fx;
            y = fy + 1;
        }
        else {
            x = fx - 1;
            y = fy;
        }
    }
}

void OptimalStrategy::ChooseFieldToShoot(int &x, int &y) {
    for (auto i : field.enemyField) {
        for (int j = 0; j < 10; ++j) {
            if (i[j] == EnemyFieldState::damaged) {
                Finish(field, x, y);
                return;
            }
        }
    }
    Scout(field, x, y);
}
