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

    bool isWinning(CellState c1,CellState c2,CellState c3)
    {
        if (c1 != c2 || c1 != c2 || c2 != c3) return false;

        return c1 != CellState::Empty;
    }

    bool didSomeoneWin(const std::array<CellState, 9> &cells)
    {
        const auto board = Utils::unwrapBoard(cells);

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
    const auto won = didSomeoneWin(m_cells);
    const auto over = won || isBoardFull(m_cells);

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




