#pragma once

#include "Utils.h"

#include "Grid.h"
#include "ImageManager.h"
#include "MainWindow.h"
#include "OptionsManager.h"
#include "OptionsWindow.h"

namespace TicTacToe
{
    class GameManager
        : public NonCopyable
        , public NonMoveable
    {
    public:
        GameManager();

        void LaunchGame();
        void PlayAt(U8 x, U8 y);
        void PlayAITurnIfNeeded();
        void Reset();
        void ShowOptionsWindow();

    private:
        Grid m_currentGrid;
        Player m_currentPlayer{ Player::Cross };
        Player m_currentOpponent{ Player::Nought };
        ImageManager m_imageManager;
        OptionsManager m_optionsManager;
        MainWindow m_mainWindow;
        OptionsWindow m_optionsWindow;
    };
}
