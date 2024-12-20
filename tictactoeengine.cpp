#include "tictactoeengine.h"
#include "computerplayer.h"
#include "utils.h"

#include <QTimer>

#include <algorithm>

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

    bool didPlayerWin(GameState gameState, Player player)
    {
        return ((gameState == GameState::WonByPlayerO && player == Player::O) ||
                (gameState == GameState::WonByPlayerX && player == Player::X));
    }
}

TicTacToeEngine::TicTacToeEngine(QObject *parent)
    : QObject{parent}
    , m_humanWins{0}
    , m_computerWins{0}
{
    restart();
}

void TicTacToeEngine::startGame(bool computerStarts)
{
    m_humanPlayer = computerStarts ? Player::O : Player::X;
    m_gameState = GameState::TurnOfPlayerX;

    emit gameStateChanged();

    if (computerStarts)
    {
        startComputerThread();
    }
}

void TicTacToeEngine::registerMove(int cellId)
{
    m_cells[cellId] = cellStateFromGameState(m_gameState);
    const auto won = Utils::didSomeoneWin(m_cells);
    const auto over = won || Utils::isBoardFull(m_cells);

    m_gameState = stateAfterMove(m_gameState, won, over);

    emit gameStateChanged();

    if (isGameOver())
    {
        if (didPlayerWin(m_gameState, computerPlayer())) m_computerWins++;
        if (didPlayerWin(m_gameState, m_humanPlayer)) m_humanWins++;

        emit winsChanged();

        QTimer::singleShot(std::chrono::milliseconds(1500), this, SLOT(restart()));
    }
}

bool TicTacToeEngine::isComputerTurn() const
{
    switch (m_gameState)
    {
        case GameState::TurnOfPlayerX:
            return computerPlayer() == Player::X;
        case GameState::TurnOfPlayerO:
            return computerPlayer() == Player::O;
        default:
            return false;
    }
}

void TicTacToeEngine::processUserChoice(int cellId)
{
    registerMove(cellId);

    if (!isGameOver())
    {
        startComputerThread();
    }
}

void TicTacToeEngine::restart()
{
    std::fill(m_cells.begin(), m_cells.end(), CellState::Empty);
    m_gameState = GameState::MainMenu;

    emit gameStateChanged();
}

Player TicTacToeEngine::computerPlayer() const
{
    return Utils::nextPlayer(m_humanPlayer);
}

void TicTacToeEngine::startComputerThread()
{
    ComputerPlayer *workerThread = new ComputerPlayer(m_cells, computerPlayer(), this);
    connect(workerThread, &ComputerPlayer::resultReady, this, &TicTacToeEngine::processComputerChoice);
    connect(workerThread, &ComputerPlayer::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

void TicTacToeEngine::processComputerChoice(int cellId)
{
    registerMove(cellId);
}




