#include "computerplayer.h"

#include <thread>

ComputerPlayer::ComputerPlayer(const std::array<CellState, 9> &board, QObject *parent) : QThread(parent), m_cells{board} {}

int ComputerPlayer::computeMove()
{
    // Simulate thinking
    std::this_thread::sleep_for(std::chrono::milliseconds(780));

    for (int i=0;i<9;++i) {
        if (m_cells[i] == CellState::Empty) return i;
    }

    return 0;
}
