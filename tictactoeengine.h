#ifndef TICTACTOEENGINE_H
#define TICTACTOEENGINE_H

#include <QObject>
#include <QQmlEngine>

#include "cellstate.h"
#include "player.h"

class TicTacToeEngine : public QObject
{
    using CellState = TicTacToeUtils::CellState;
    using Player = TicTacToeUtils::Player;

    Q_OBJECT
    Q_PROPERTY(QList<CellState> cells READ getCells NOTIFY cellsChanged);
    Q_PROPERTY(bool isComputerTurn READ isComputerTurn NOTIFY computerTurnChanged);
    QML_ELEMENT
public:
    explicit TicTacToeEngine(QObject *parent = nullptr);

    Q_INVOKABLE QList<CellState> getCells() const {return QList(m_cells.begin(), m_cells.end());}
    Q_INVOKABLE void processUserChoice(int cellId);
    Q_INVOKABLE void reset();
    Q_INVOKABLE bool isComputerTurn() const {return m_computerTurn;}

signals:
    void cellsChanged();
    void computerTurnChanged();

public slots:
    void processComputerChoice(int cellId);

private:
    std::array<CellState, 9> m_cells;
    Player m_nextPlayer;
    bool m_computerTurn;

    void startComputerThread();
    void registerMove(int cellId);
};

#endif // TICTACTOEENGINE_H
