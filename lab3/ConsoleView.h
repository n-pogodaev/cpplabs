#pragma once
#include "GameView.h"
#include <iostream>

class ConsoleView : public GameView {
public:
    ConsoleView() = default;
    ~ConsoleView() override = default;
    void Start() override;
    void Show(Gamer *g) override;
    void Clear() override;
    void Stop() override;
};
