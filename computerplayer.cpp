#include "computerplayer.h"
#include "player.h"
#include "utils.h"

#include <thread>

ComputerPlayer::ComputerPlayer(const std::array<CellState, 9> &board, Player player, QObject *parent) : QThread(parent), m_cells{board}, m_player{player} {}

namespace {
    using Cells = std::array<CellState, 9>;

    int minimax(Cells &cells, Player currentPlayer)
    {
        if (Utils::didSomeoneWin(cells)) {
            return -1;
        }

        if (Utils::isBoardFull(cells)) {
            return 0;
        }

        int best = -1;

        for (size_t i=0;i<9;++i)
        {
            if (cells[i] == CellState::Empty)
            {
                cells[i] = Utils::playerToCellState(currentPlayer);
                const auto child = -minimax(cells, Utils::nextPlayer(currentPlayer));
                cells[i] = CellState::Empty;

                best = std::max(best, child);
            }
        }

        return best;
    }
}


int ComputerPlayer::computeMove()
{
    // Simulate thinking
    std::this_thread::sleep_for(std::chrono::milliseconds(780));

    int bestValue = -1;
    size_t bestMove = 0;

    for (size_t i=0;i<9;++i) {
        if (m_cells[i] == CellState::Empty)
        {
            m_cells[i] = Utils::playerToCellState(m_player);
            const auto result = -minimax(m_cells, Utils::nextPlayer(m_player));
            m_cells[i] = CellState::Empty;

            if (result > bestValue)
            {
                bestMove = i;
                bestValue = result;
            }
        }
    }

    return bestMove;
}
