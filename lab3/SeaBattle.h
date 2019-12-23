#pragma once
#include "ConsoleView.h"
#include "GraphicView.h"
#include "OptimalStrategy.h"
#include "RandomStrategy.h"
#include "ManualStrategy.h"
#include "Gamer.h"

enum class ViewType {
    graphic, console
};

class SeaBattle {
    GameView *view;
    Gamer *g1, *g2;
    bool IsEnd();
    void Play();
    void PlaceShips(Gamer *g);
public:
    SeaBattle(StrategyType firstGamerPlaceStrategy, StrategyType firstGamerPlayStrategy,
            StrategyType secondGamerPlaceStrategy, StrategyType secondGamerPlayStrategy, ViewType vt);
    ~SeaBattle();
    void StartGame();
};
