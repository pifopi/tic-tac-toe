#include "AIManager.h"
#include "GameManager.h"
#include "MainWindow.h"
#include "OptionManager.h"

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>

namespace TicTacToe
{
    GameManager& GameManager::Instance()
    {
        static GameManager instance;
        return instance;
    }

    void GameManager::LaunchGame()
    {
        if (OptionManager::Instance().GetAI(m_currentPlayer))
        {
            PlayAITurn();
        }
        MainWindow::Instance().show();
    }

    bool GameManager::GetVictory(const Map& map, const Player& player) const
    {
        std::array<Player, 3> topRow{{map[0][0], map[0][1], map[0][2]}};
        std::array<Player, 3> midRow{{map[1][0], map[1][1], map[1][2]}};
        std::array<Player, 3> botRow{{map[2][0], map[2][1], map[2][2]}};

        std::array<Player, 3> leftColumn{{map[0][0], map[1][0], map[2][0]}};
        std::array<Player, 3> midColumn{{map[0][1], map[1][1], map[2][1]}};
        std::array<Player, 3> rightColumn{{map[0][2], map[1][2], map[2][2]}};

        std::array<Player, 3> diagonal{{map[0][0], map[1][1], map[2][2]}};
        std::array<Player, 3> anteDiagonal{{map[2][0], map[1][1], map[0][2]}};

        if (std::all_of(topRow.begin(), topRow.end(), [&player] (const Player& i) {return i == player; }) ||
            std::all_of(midRow.begin(), midRow.end(), [&player] (const Player& i) {return i == player; }) ||
            std::all_of(botRow.begin(), botRow.end(), [&player] (const Player& i) {return i == player; }) ||
            std::all_of(leftColumn.begin(), leftColumn.end(), [&player] (const Player& i) {return i == player; }) ||
            std::all_of(midColumn.begin(), midColumn.end(), [&player] (const Player& i) {return i == player; }) ||
            std::all_of(rightColumn.begin(), rightColumn.end(), [&player] (const Player& i) {return i == player; }) ||
            std::all_of(diagonal.begin(), diagonal.end(), [&player] (const Player& i) {return i == player; }) ||
            std::all_of(anteDiagonal.begin(), anteDiagonal.end(), [&player] (const Player& i) {return i == player; })
            )
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool GameManager::IsMapFull(const Map& map) const
    {
        for (auto& row : map)
        {
            for (auto& elem : row)
            {
                if (elem == Player::Empty)
                {
                    return false;
                }
            }
        }
        return true;
    }

    const Map& GameManager::GetMap() const
    {
        return m_currentMap;
    }

    const Player& GameManager::GetCurrentPlayer() const
    {
        return m_currentPlayer;
    }

    const Player& GameManager::GetCurrentOpponent() const
    {
        return m_currentOpponent;
    }

    void GameManager::PlayAt(const U8& x, const U8& y)
    {
        m_currentMap[x][y] = m_currentPlayer;
        std::swap(m_currentPlayer, m_currentOpponent);
        MainWindow::Instance().UpdateButtons();

        //opponent because we just swaped
        if (GetVictory(m_currentMap, m_currentOpponent))
        {
            MainWindow::Instance().DisplayEndGame(m_currentOpponent);
        }
        else if (IsMapFull(m_currentMap))
        {
            MainWindow::Instance().DisplayEndGame(Player::Empty);
        }

        if (OptionManager::Instance().GetAI(m_currentPlayer))
        {
            PlayAITurn();
        }
    }

    void GameManager::PlayAITurn()
    {
        auto moves = AIManager::Instance().GetBestMoves();
        auto random = std::rand() % moves.size();
        auto move = moves[random];

        PlayAt(move.first, move.second);
    }

    void GameManager::Reset()
    {
        m_currentPlayer = Player::Cross;
        m_currentOpponent = Player::Nought;

        for (auto& row : m_currentMap)
        {
            for (auto& elem : row)
            {
                elem = Player::Empty;
            }
        }
        MainWindow::Instance().UpdateButtons();

        if (OptionManager::Instance().GetAI(m_currentPlayer))
        {
            PlayAITurn();
        }
    }

    GameManager::GameManager()
        : m_currentPlayer(Player::Cross)
        , m_currentOpponent(Player::Nought)
    {
        std::srand(std::time(nullptr));
    }
}
