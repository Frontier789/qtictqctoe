#include <algorithm>

#include "tictactoeengine.h"
#include "computerplayer.h"

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

void TicTacToeEngine::registerMove(int cellId)
{
    m_cells[cellId] = cellStateFromPlayer(m_nextPlayer);
    m_nextPlayer = rollNextPlayer(m_nextPlayer);
    m_computerTurn = !m_computerTurn;

    emit computerTurnChanged();
    emit cellsChanged();

}

void TicTacToeEngine::processUserChoice(int cellId)
{
    qDebug() << "User pressed cell " << cellId;

    registerMove(cellId);
    startComputerThread();
}

void TicTacToeEngine::reset()
{
    std::fill(m_cells.begin(), m_cells.end(), CellState::Empty);
    m_nextPlayer = Player::X;
    m_computerTurn = false;

    emit computerTurnChanged();
    emit cellsChanged();
}

void TicTacToeEngine::startComputerThread()
{
    ComputerPlayer *workerThread = new ComputerPlayer(m_cells, this);
    connect(workerThread, &ComputerPlayer::resultReady, this, &TicTacToeEngine::processComputerChoice);
    connect(workerThread, &ComputerPlayer::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

void TicTacToeEngine::processComputerChoice(int cellId)
{
    qDebug() << "AI picked cell " << cellId;

    registerMove(cellId);
}




