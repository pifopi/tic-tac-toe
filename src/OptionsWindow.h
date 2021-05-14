#pragma once

#include "Utils.h"

#include <QDialog>

namespace TicTacToe
{
    class GameManager;
    class OptionsManager;

    class OptionsWindow
        : public QDialog
    {
        Q_OBJECT
    public:
        OptionsWindow(OptionsManager& optionsManager, GameManager& gameManager);
    };
}
