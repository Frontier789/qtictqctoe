#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <QThread>

#include "cellstate.h"
#include "player.h"

class ComputerPlayer : public QThread
{
    Q_OBJECT
    void run() override {
        const auto result = computeMove();
        emit resultReady(result);
    }

public:
    ComputerPlayer(const std::array<CellState, 9> &board, Player me, QObject *parent = nullptr);

signals:
    void resultReady(int cellId);

private:
    int computeMove();

    std::array<CellState, 9> m_cells;
    Player m_player;
};

#endif // COMPUTERPLAYER_H
