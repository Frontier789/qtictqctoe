#ifndef CELLSTATE_H
#define CELLSTATE_H

#include <QObject>
#include <qqml.h>

namespace TicTacToeUtils
{
    Q_NAMESPACE

    enum class CellState
    {
        Empty,
        FullX,
        FullO
    };
    Q_ENUM_NS(CellState)
}

#endif // CELLSTATE_H
