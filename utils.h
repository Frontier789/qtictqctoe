#ifndef UTILS_H
#define UTILS_H

#include <array>

#include "cellstate.h"
#include "player.h"

namespace Utils
{
    bool didSomeoneWin(const std::array<CellState, 9> &cells);
    bool isBoardFull(const std::array<CellState, 9> &cells);

    CellState playerToCellState(Player player);
    Player nextPlayer(Player player);
}

#endif // UTILS_H
