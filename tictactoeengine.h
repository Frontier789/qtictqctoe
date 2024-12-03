#ifndef TICTACTOEENGINE_H
#define TICTACTOEENGINE_H

#include <QObject>
#include <QQmlEngine>

class TicTacToeEngine : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit TicTacToeEngine(QObject *parent = nullptr);

signals:

public:
    Q_INVOKABLE void processUserChoice(int cellId);
};

#endif // TICTACTOEENGINE_H
