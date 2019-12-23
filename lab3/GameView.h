#pragma once
#include "Gamer.h"

class GameView {
public:
    GameView() = default;
    virtual ~GameView() = default;
    virtual void Start() = 0;
    virtual void Show(Gamer *) = 0;
    virtual void Clear() = 0;
    virtual void Stop() = 0;
};
