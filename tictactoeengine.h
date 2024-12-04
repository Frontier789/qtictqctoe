#ifndef TICTACTOEENGINE_H
#define TICTACTOEENGINE_H

#include <QObject>
#include <QQmlEngine>

#include "cellstate.h"
#include "gamestate.h"
#include "player.h"

class TicTacToeEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<CellState> cells READ getCells NOTIFY gameStateChanged);
    Q_PROPERTY(bool isComputerTurn READ isComputerTurn NOTIFY gameStateChanged);
    Q_PROPERTY(bool isGameOver READ isGameOver NOTIFY gameStateChanged);
    Q_PROPERTY(bool isInMenu READ isInMenu NOTIFY gameStateChanged);
    Q_PROPERTY(size_t humanWins READ humanWins NOTIFY winsChanged);
    Q_PROPERTY(size_t computerWins READ computerWins NOTIFY winsChanged);
    Q_PROPERTY(GameState gameState READ gameState NOTIFY gameStateChanged);
    QML_ELEMENT
public:
    explicit TicTacToeEngine(QObject *parent = nullptr);

    Q_INVOKABLE QList<CellState> getCells() const {return QList(m_cells.begin(), m_cells.end());}
    Q_INVOKABLE void processUserChoice(int cellId);
    Q_INVOKABLE void startGame(bool computerStarts);

    Q_INVOKABLE bool isInMenu() const {return m_gameState == GameState::MainMenu;}
    Q_INVOKABLE bool isComputerTurn() const;
    Q_INVOKABLE bool isGameOver() const {return m_gameState == GameState::WonByPlayerO || m_gameState == GameState::WonByPlayerX || m_gameState == GameState::Draw;}

    Q_INVOKABLE GameState gameState() const {return m_gameState;}
    Q_INVOKABLE size_t humanWins() const {return m_humanWins;}
    Q_INVOKABLE size_t computerWins() const {return m_computerWins;}

signals:
    void gameStateChanged();
    void winsChanged();

public slots:
    void processComputerChoice(int cellId);
    void restart();

private:
    std::array<CellState, 9> m_cells;
    Player m_humanPlayer;
    GameState m_gameState;
    size_t m_humanWins;
    size_t m_computerWins;

    Player computerPlayer() const;

    void startComputerThread();
    void registerMove(int cellId);
};

#endif // TICTACTOEENGINE_H
