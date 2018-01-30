#pragma once

#include "Utils.h"

namespace TicTacToe
{
    class GameManager
        : public NonCopyable
    {
    public:
        static GameManager& Instance();

        void LaunchGame();
        bool GetVictory(const Map& map, const Player& player) const;
        bool IsMapFull(const Map& map) const;
        const Map& GetMap() const;
        const Player& GetCurrentPlayer() const;
        const Player& GetCurrentOpponent() const;
        void PlayAt(const U8& x, const U8& y);
        void PlayAITurn();
        void Reset();

    private:
        GameManager();

        Map m_currentMap;
        Player m_currentPlayer;
        Player m_currentOpponent;
    };
}
