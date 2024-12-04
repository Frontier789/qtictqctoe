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
    QML_ELEMENT
public:
    explicit TicTacToeEngine(QObject *parent = nullptr);

    Q_INVOKABLE QList<CellState> getCells() const {return QList(m_cells.begin(), m_cells.end());}
    Q_INVOKABLE void processUserChoice(int cellId);
    Q_INVOKABLE void reset();

signals:
    void cellsChanged(); // TODO: delete if not used

private:
    std::array<CellState, 9> m_cells;
    Player m_nextPlayer;
};

#endif // TICTACTOEENGINE_H
