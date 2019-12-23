#pragma once
#include "GameView.h"

class GraphicView : public GameView {
public:
    GraphicView() = default;
    ~GraphicView() override = default;
    void Start() override {}
    void Show(Gamer *g) override {}
    void Clear() override {}
    void Stop() override {}
};
