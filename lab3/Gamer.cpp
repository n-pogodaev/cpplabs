#include "Gamer.h"
#include <algorithm>
#include <iostream>

Gamer::Gamer(StrategyType placeStrat, StrategyType playStrat) {
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            field.enemyField[i][j] = EnemyFieldState::unknown;
            field.yourField[i][j] = YourFieldState::empty;
        }
    }
    switch (placeStrat) {
        case StrategyType::random:
            placeStrategy = new RandomStrategy(field);
            isRealPlacing = false;
            break;
        case StrategyType::manual:
            placeStrategy = new ManualStrategy(field);
            isRealPlacing = true;
            break;
        case StrategyType::optimal:
            placeStrategy = new OptimalStrategy(field);
            isRealPlacing = false;
            break;
    }
    switch (playStrat) {
        case StrategyType::random:
            playStrategy = new RandomStrategy(field);
            isRealPlaying = false;
            break;
        case StrategyType::manual:
            playStrategy = new ManualStrategy(field);
            isRealPlaying = true;
            break;
        case StrategyType::optimal:
            playStrategy = new OptimalStrategy(field);
            isRealPlaying = false;
            break;
    }
}

Gamer::~Gamer() {
    delete placeStrategy;
    delete playStrategy;
}

void PlaceShip(Field &field, int count, int x1, int y1, int x2, int y2) {
    int decksNum = GetDecksNumberByShipNumber(count);
    Ship &ship = field.ships[count];
    if (x1 > x2) {
        std::swap(x1, x2);
    }
    if (y1 > y2) {
        std::swap(y1, y2);
    }
    if (y2 - y1 == decksNum - 1 && x1 == x2) {
        ship.SetCoords(x1, y1, x1, y1 + 1, x1, y1 + 2, x1, y1 + 3);
        for (int i = 0; i < decksNum; ++i) {
            if (DoesHaveAdjacentShips(field, x1, y1 + i)) {
                throw StrategyLogicException();
            }
        }
        for (int i = 0; i < decksNum; ++i) {
            field.yourField[y1 + i - 1][x1 - 1] = YourFieldState::ship;
        }
    }
    else if (x2 - x1 == decksNum - 1 && y1 == y2) {
        ship.SetCoords(x1, y1, x1 + 1, y1, x1 + 2, y1, x1 + 3, y1);
        for (int i = 0; i < decksNum; ++i) {
            if (DoesHaveAdjacentShips(field, x1 + i, y1)) {
                throw StrategyLogicException();
            }
        }
        for (int i = 0; i < decksNum; ++i) {
            field.yourField[y1 - 1][x1 + i - 1] = YourFieldState::ship;
        }
    }
    else {
        throw StrategyLogicException();
    }
}

void Gamer::PlaceNextShip() {
    if (field.shipsCount > 10) return;
    int x1, y1, x2, y2;
    int decksNum = GetDecksNumberByShipNumber(field.shipsCount);
    while (true) {
        placeStrategy->ChooseFieldsToPlaceShip(decksNum, x1, y1, x2, y2);
        if (x1 < 1 || x1 > 10 || y1 < 1 || y1 > 10 || x2 < 1 || x2 > 10 || y2 < 1 || y2 > 10) {
            throw StrategyLogicException();
        }
        try {
            PlaceShip(field, field.shipsCount, x1, y1, x2, y2);
        }
        catch (StrategyLogicException &e) {
            if (IsRealPlacing()) {
                std::cout << "wrong ship position, try again" << std::endl;
                continue;
            }
            else {
                throw;
            }
        }
        break;
    }
    ++field.shipsCount;
}

void Gamer::Shoot(Gamer *enemy) {
    int x, y;
    playStrategy->ChooseFieldToShoot(x, y);
    if (x < 1 || x > 10 || y < 1 || y > 10) {
        throw StrategyLogicException();
    }
    if (enemy->field.yourField[y - 1][x - 1] == YourFieldState::empty) {
        enemy->field.yourField[y - 1][x - 1] = YourFieldState::miss;
        field.enemyField[y - 1][x - 1] = EnemyFieldState::miss;
    }
    else if (enemy->field.yourField[y - 1][x - 1] == YourFieldState::ship) {
        enemy->field.yourField[y - 1][x - 1] = YourFieldState::shot;
        Deck *shotDeck = nullptr;
        for (auto & ship : enemy->field.ships) {
            if (ship.DeckByCoords(x, y, &shotDeck)) {
                shotDeck->isShot = true;
                if (ship.IsWrecked()) {
                    for (int i = 0; i < ship.decksNum; ++i) {
                        field.enemyField[ship.decks[i].y - 1][ship.decks[i].x - 1] = EnemyFieldState::wrecked;
                    }
                }
                else {
                    field.enemyField[y - 1][x - 1] = EnemyFieldState::damaged;
                }
                return;
            }
        }
        throw StrategyLogicException();
    }
}

bool Gamer::IsDefeated() {
    for (auto & ship : field.ships) {
        if (!ship.IsWrecked()) {
            return false;
        }
    }
    return true;
}
