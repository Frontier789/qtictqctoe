#include "utils.h"

namespace {
    using Board = std::array<std::array<CellState, 3>, 3>;

    Board unwrapBoard(const std::array<CellState, 9> &board)
    {
        Board unwrapped;

        for (size_t i=0;i<9;++i)
        {
            unwrapped[i%3][i/3] = board[i];
        }

        return unwrapped;
    }

    bool isWinning(CellState c1,CellState c2,CellState c3)
    {
        if (c1 != c2 || c1 != c2 || c2 != c3) return false;

        return c1 != CellState::Empty;
    }
}

namespace Utils
{
    bool didSomeoneWin(const std::array<CellState, 9> &cells)
    {
        const auto board = unwrapBoard(cells);

        for (int i=0;i<3;++i) {
            if (isWinning(board[i][0], board[i][1], board[i][2])) return true;
            if (isWinning(board[0][i], board[1][i], board[2][i])) return true;
        }

        if (isWinning(board[0][0], board[1][1], board[2][2])) return true;
        if (isWinning(board[0][2], board[1][1], board[2][0])) return true;

        return false;
    }

    bool isBoardFull(const std::array<CellState, 9> &cells)
    {
        for (const auto cell : cells) {
            if (cell == CellState::Empty) return false;
        }

        return true;
    }

    CellState playerToCellState(Player player)
    {
        switch (player)
        {
            case Player::O: return CellState::FullO;
            case Player::X: return CellState::FullX;
            default:
                // Should never happen
                throw std::runtime_error("Enum out of range");
        }
    }

    Player nextPlayer(Player player)
    {
        switch (player)
        {
        case Player::O: return Player::X;
        case Player::X: return Player::O;
        default:
            // Should never happen
            throw std::runtime_error("Enum out of range");
        }
    }
}
