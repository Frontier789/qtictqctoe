#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QObject>
#include <qqml.h>

namespace GameStateNS
{
    Q_NAMESPACE

    enum class GameState
    {
        MainMenu,
        TurnOfPlayerO,
        TurnOfPlayerX,
        WonByPlayerO,
        WonByPlayerX,
        Draw,
    };
    Q_ENUM_NS(GameState)
}

using GameStateNS::GameState;

#endif // GAMESTATE_H
