#ifndef CELLSTATE_H
#define CELLSTATE_H

#include <QObject>
#include <qqml.h>

namespace CellStateNS
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

using CellStateNS::CellState;

#endif // CELLSTATE_H
