#include <algorithm>

#include "tictactoeengine.h"

namespace
{
    using namespace TicTacToeUtils;

    CellState cellStateFromPlayer(Player player)
    {
        switch (player) {
            case Player::X:
                return CellState::FullX;
            case Player::O:
                return CellState::FullO;
            default:
                // Should never happen
                throw std::runtime_error("Enum out of range");
        }
    }

    Player rollNextPlayer(Player player)
    {
        switch (player) {
            case Player::X:
                return Player::O;
            case Player::O:
                return Player::X;
            default:
                // Should never happen
                throw std::runtime_error("Enum out of range");
        }
    }
}

TicTacToeEngine::TicTacToeEngine(QObject *parent)
    : QObject{parent}
{
    reset();
}

void TicTacToeEngine::processUserChoice(int cellId)
{
    qDebug() << "User pressed cell " << cellId;

    m_cells[cellId] = cellStateFromPlayer(m_nextPlayer);
    m_nextPlayer = rollNextPlayer(m_nextPlayer);

    emit cellsChanged();
}

void TicTacToeEngine::reset()
{
    std::fill(m_cells.begin(), m_cells.end(), CellState::Empty);
    m_nextPlayer = Player::X;

    emit cellsChanged();
}
