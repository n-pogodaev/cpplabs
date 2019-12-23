#pragma once
#include "Field.h"

enum class StrategyType {
    random, manual, optimal
};

class Strategy {
protected:
    const Field &field;
public:
    explicit Strategy(const Field &f) : field(f) {}
    virtual ~Strategy() = default;
    virtual void ChooseFieldToShoot(int &x, int &y) = 0;
    virtual void ChooseFieldsToPlaceShip(int decksNum, int &x1, int &y1, int &x2, int &y2) = 0;
};
