#include "RandomStrategy.h"
#include <ctime>

void RandomStrategy::ChooseFieldToShoot(int &x, int &y) {
    int notShotFields = 0;
    for (auto i : field.enemyField) {
        for (int j = 0; j < 10; ++j) {
            if (i[j] == EnemyFieldState::unknown) {
                ++notShotFields;
            }
        }
    }
    srand(time(nullptr));
    int pickedFieldNum = (rand() % notShotFields) + 1;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (field.enemyField[i][j] == EnemyFieldState::unknown) {
                --pickedFieldNum;
                if (pickedFieldNum == 0) {
                    y = i + 1;
                    x = j + 1;
                }
            }
        }
    }
}

bool CheckUpperFields(const Field &field, int decksNum, int x, int y) {
    if (y < decksNum) {
        return false;
    }
    for (int i = 1; i < decksNum; ++i) {
        if (DoesHaveAdjacentShips(field, x, y - i)) {
            return false;
        }
    }
    return true;
}

bool CheckLowerFields(const Field &field, int decksNum, int x, int y) {
    if (y > 10 - decksNum + 1) {
        return false;
    }
    for (int i = 1; i < decksNum; ++i) {
        if (DoesHaveAdjacentShips(field, x, y + i)) {
            return false;
        }
    }
    return true;
}

bool CheckLeftFields(const Field &field, int decksNum, int x, int y) {
    if (x < decksNum) {
        return false;
    }
    for (int i = 1; i < decksNum; ++i) {
        if (DoesHaveAdjacentShips(field, x - i, y)) {
            return false;
        }
    }
    return true;
}

bool CheckRightFields(const Field &field, int decksNum, int x, int y) {
    if (x > 10 - decksNum + 1) {
        return false;
    }
    for (int i = 1; i < decksNum; ++i) {
        if (DoesHaveAdjacentShips(field, x + i, y)) {
            return false;
        }
    }
    return true;
}

void RandomStrategy::ChooseFieldsToPlaceShip(int decksNum, int &x1, int &y1, int &x2, int &y2) {
    int freeFieldsCount = 0;
    int freeFields[100];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (!DoesHaveAdjacentShips(field, j + 1, i + 1)) {
                freeFields[freeFieldsCount] = i * 10 + j;
                ++freeFieldsCount;
            }
        }
    }
    srand(time(nullptr));
    while (true) {
        int pickedFieldNum = (rand() % freeFieldsCount) + 1;
        x1 = freeFields[pickedFieldNum - 1] % 10 + 1;
        y1 = freeFields[pickedFieldNum - 1] / 10 + 1;
        if (CheckUpperFields(field, decksNum, x1, y1)) {
            x2 = x1;
            y2 = y1 - decksNum + 1;
        }
        else if (CheckRightFields(field, decksNum, x1, y1)) {
            x2 = x1 + decksNum - 1;
            y2 = y1;
        }
        else if (CheckLowerFields(field, decksNum, x1, y1)) {
            x2 = x1;
            y2 = y1 + decksNum - 1;
        }
        else if (CheckLeftFields(field, decksNum, x1, y1)) {
            x2 = x1 - decksNum + 1;
            y2 = y1;
        }
        else {
            continue;
        }
        break;
    }
}
