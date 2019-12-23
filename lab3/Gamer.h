#pragma once
#include "RandomStrategy.h"
#include "OptimalStrategy.h"
#include "ManualStrategy.h"
#include "Field.h"

class StrategyLogicException : std::exception {
public:
    StrategyLogicException() = default;
    ~StrategyLogicException() override = default;
    const char *what() const noexcept override {
        return "Wrong strategy logic";
    }
};

class Gamer {
    friend class ConsoleView;
    friend class GraphicView;
private:
    Field field;
    Strategy *placeStrategy = nullptr;
    Strategy *playStrategy = nullptr;
    bool isRealPlacing = true;
    bool isRealPlaying = true;
public:
    explicit Gamer(StrategyType placeStrategy, StrategyType playStrategy);
    ~Gamer();
    void PlaceNextShip();
    void Shoot(Gamer *);
    bool IsDefeated();
    bool IsRealPlaying() { return isRealPlaying; }
    bool IsRealPlacing() { return isRealPlacing; }
};
