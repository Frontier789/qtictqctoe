#include <algorithm>

#include "tictactoeengine.h"
#include "computerplayer.h"
#include "utils.h"

namespace
{
    CellState cellStateFromGameState(GameState gameState)
    {
        switch (gameState) {
            case GameState::TurnOfPlayerX:
                return CellState::FullX;
            case GameState::TurnOfPlayerO:
                return CellState::FullO;
            default:
                // Should never happen
                throw std::runtime_error("Enum out of range");
        }
    }

    GameState stateAfterMove(GameState gameState, bool won, bool over)
    {
        if (!won && over) return GameState::Draw;

        switch (gameState) {
        case GameState::TurnOfPlayerX:
            if (won) return GameState::WonByPlayerX;
            else return GameState::TurnOfPlayerO;
        case GameState::TurnOfPlayerO:
            if (won) return GameState::WonByPlayerO;
            else return GameState::TurnOfPlayerX;
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
    m_cells[cellId] = cellStateFromGameState(m_gameState);
    const auto won = Utils::didSomeoneWin(m_cells);
    const auto over = won || Utils::isBoardFull(m_cells);

    m_gameState = stateAfterMove(m_gameState, won, over);

    emit gameStateChanged();
}

void TicTacToeEngine::processUserChoice(int cellId)
{
    qDebug() << "User pressed cell " << cellId;

    registerMove(cellId);

    if (m_gameState == GameState::TurnOfPlayerO)
    {
        startComputerThread();
    }
}

void TicTacToeEngine::reset()
{
    std::fill(m_cells.begin(), m_cells.end(), CellState::Empty);
    m_gameState = GameState::TurnOfPlayerX;

    emit gameStateChanged();
}

void TicTacToeEngine::startComputerThread()
{
    ComputerPlayer *workerThread = new ComputerPlayer(m_cells, Player::O, this);
    connect(workerThread, &ComputerPlayer::resultReady, this, &TicTacToeEngine::processComputerChoice);
    connect(workerThread, &ComputerPlayer::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

void TicTacToeEngine::processComputerChoice(int cellId)
{
    qDebug() << "AI picked cell " << cellId;

    registerMove(cellId);
}




