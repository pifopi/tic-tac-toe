#pragma once

#include "Utils.h"

#include <QDialog>

namespace TicTacToe
{
    class GameManager;
    class OptionsManager;

    class OptionsWindow
        : public QDialog
        , public NonCopyable
        , public NonMoveable
    {
        Q_OBJECT
    public:
        OptionsWindow(OptionsManager& optionsManager, GameManager& gameManager);
    };
}
