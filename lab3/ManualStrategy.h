#pragma once
#include "Strategy.h"

class ManualStrategy: public Strategy {
public:
    explicit ManualStrategy(const Field &f) : Strategy(f) {}
    ~ManualStrategy() override = default;
    void ChooseFieldToShoot(int &x, int &y) override;
    void ChooseFieldsToPlaceShip(int decksNum, int &x1, int &y1, int &x2, int &y2) override;
};
