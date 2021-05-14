#include "GameManager.h"

#include "AI.h"
#include "EndGameChecker.h"
#include "MainWindow.h"
#include "OptionsManager.h"

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <QCoreApplication>

namespace TicTacToe
{
    GameManager::GameManager()
        : m_currentGrid()
        , m_imageManager()
        , m_optionsManager()
        , m_mainWindow(m_currentGrid, m_imageManager, *this)
        , m_optionsWindow(m_optionsManager, *this)
    {
        std::srand(std::time(nullptr));
    }

    void GameManager::LaunchGame()
    {
        m_mainWindow.show();
        PlayAITurnIfNeeded();
    }

    void GameManager::PlayAt(const U8 x, const U8 y)
    {
        m_currentGrid[x][y] = m_currentPlayer;
        std::swap(m_currentPlayer, m_currentOpponent);
        m_mainWindow.UpdateButtons(m_currentGrid, m_imageManager);

        //opponent because we just swaped
        if (EndGameChecker::IsVictoryFor(m_currentGrid, m_currentOpponent))
        {
            m_mainWindow.DisplayEndGame(m_currentOpponent, *this);
        }
        else if (EndGameChecker::IsGridFull(m_currentGrid))
        {
            m_mainWindow.DisplayEndGame(Player::Empty, *this);
        }

        QCoreApplication::processEvents();
        PlayAITurnIfNeeded();
    }

    void GameManager::PlayAITurnIfNeeded()
    {
        if (m_optionsManager.IsAI(m_currentPlayer))
        {
            const auto moves = AI::GetBestMoves(m_currentGrid, m_currentPlayer, m_currentOpponent);
            const auto random = std::rand() % moves.size();
            const auto& move = moves[random];

            PlayAt(move.first, move.second);
        }
    }

    void GameManager::Reset()
    {
        m_currentPlayer = Player::Cross;
        m_currentOpponent = Player::Nought;

        for (auto& row : m_currentGrid)
        {
            for (auto& elem : row)
            {
                elem = Player::Empty;
            }
        }
        m_mainWindow.UpdateButtons(m_currentGrid, m_imageManager);

        PlayAITurnIfNeeded();
    }

    void GameManager::ShowOptionsWindow()
    {
        m_optionsWindow.exec();
    }
}
