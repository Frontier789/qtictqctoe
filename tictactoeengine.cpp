#include "tictactoeengine.h"

TicTacToeEngine::TicTacToeEngine(QObject *parent)
    : QObject{parent}
{}

void TicTacToeEngine::processUserChoice(int cellId)
{
    qDebug() << "User pressed cell " << cellId;
}
