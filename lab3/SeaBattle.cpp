#include "SeaBattle.h"

bool SeaBattle::IsEnd() {
    return g1->IsDefeated() || g2->IsDefeated();
}

SeaBattle::SeaBattle(StrategyType firstGamerPlaceStrategy, StrategyType firstGamerPlayStrategy,
                     StrategyType secondGamerPlaceStrategy, StrategyType secondGamerPlayStrategy,
                     ViewType vt) : g1(nullptr), g2(nullptr), view(nullptr){
    g1 = new Gamer(firstGamerPlaceStrategy, firstGamerPlayStrategy);
    g2 = new Gamer(secondGamerPlaceStrategy, secondGamerPlayStrategy);
    switch (vt) {
        case ViewType::graphic:
            view = new GraphicView();
            break;
        case ViewType::console:
            view = new ConsoleView();
            break;
    }
}

SeaBattle::~SeaBattle() {
    delete g1;
    delete g2;
    delete view;
}

void SeaBattle::Play() {
    while (!IsEnd()) {
        if (g1->IsRealPlaying()) {
            view->Stop();
            view->Clear();
            view->Show(g1);
            g1->Shoot(g2);
            view->Clear();
            view->Show(g1);
            view->Stop();
            view->Clear();
        }
        else {
            g1->Shoot(g2);
        }
        if (IsEnd()) break;
        if (g2->IsRealPlaying()) {
            view->Stop();
            view->Clear();
            view->Show(g2);
            g2->Shoot(g1);
            view->Clear();
            view->Show(g2);
            view->Stop();
            view->Clear();
        }
        else {
            g2->Shoot(g1);
        }
    }
}

void SeaBattle::PlaceShips(Gamer *g) {
    for (int i = 0; i < 10; ++i) {
        if (g->IsRealPlacing()) {
            view->Show(g);
            g->PlaceNextShip();
            view->Clear();
        }
        else {
            g->PlaceNextShip();
        }
    }
}

void SeaBattle::StartGame() {
    view->Start();
    PlaceShips(g1);
    if (g2->IsRealPlacing()) {
        view->Stop();
    }
    PlaceShips(g2);
    Play();
    view->Show(g1);
    view->Show(g2);
    if (g1->IsDefeated()) {
        std::cout << "PLAYER 2 WINS" << std::endl;
    }
    else {
        std::cout << "PLAYER 1 WINS" << std::endl;
    }
    view->Stop();
    view->Clear();
}
