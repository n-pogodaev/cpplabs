#pragma once
#include "Strategy.h"

class OptimalStrategy : public Strategy {
    Field optimalField;
public:
    explicit OptimalStrategy(const Field &f);
    ~OptimalStrategy() override = default;
    void ChooseFieldToShoot(int &x, int &y) override;
    void ChooseFieldsToPlaceShip(int decksNum, int &x1, int &y1, int &x2, int &y2) override;
};
