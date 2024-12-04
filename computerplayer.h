#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <QThread>

#include "cellstate.h"

class ComputerPlayer : public QThread
{
    using CellState = TicTacToeUtils::CellState;

    Q_OBJECT
    void run() override {
        const auto result = computeMove();
        emit resultReady(result);
    }

public:
    ComputerPlayer(const std::array<CellState, 9> &board, QObject *parent = nullptr);

signals:
    void resultReady(int cellId);

private:
    int computeMove();

    std::array<CellState, 9> m_cells;
};

#endif // COMPUTERPLAYER_H
