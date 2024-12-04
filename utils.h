#ifndef UTILS_H
#define UTILS_H

#include <array>

#include "cellstate.h"

namespace Utils
{
    inline std::array<std::array<CellState, 3>, 3> unwrapBoard(const std::array<CellState, 9> &board)
    {
        std::array<std::array<CellState, 3>, 3> unwrapped;

        for (size_t i=0;i<9;++i)
        {
            unwrapped[i%3][i/3] = board[i];
        }

        return unwrapped;
    }
}

#endif // UTILS_H
