#include "GameManager.h"

#include <QApplication>

//#include "vld.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    TicTacToe::GameManager::Instance().LaunchGame();

    return app.exec();
}
