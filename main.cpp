#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "tictactoeengine.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine; 
    TicTacToeEngine ticTacToe{&app};
    engine.rootContext()->setContextProperty("ticTacToe", &ticTacToe);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("qtictactoe", "Main");

    return app.exec();
}
