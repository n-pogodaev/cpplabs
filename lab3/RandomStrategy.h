#pragma once
#include "Strategy.h"

class RandomStrategy : public Strategy {
public:
    explicit RandomStrategy(const Field &f) : Strategy(f) {}
    ~RandomStrategy() override = default;
    void ChooseFieldToShoot(int &x, int &y) override;
    void ChooseFieldsToPlaceShip(int decksNum, int &x1, int &y1, int &x2, int &y2) override;
};
