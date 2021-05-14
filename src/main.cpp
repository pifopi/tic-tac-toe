#include "GameManager.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    TicTacToe::GameManager gameManager;
    gameManager.LaunchGame();

    return app.exec();
}
