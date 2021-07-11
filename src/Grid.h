#pragma once

#include "Utils.h"

namespace TicTacToe
{
    class Grid
    {
    public:
        void Set(U8 x, U8 y, Player player);
        Player Get(U8 x, U8 y) const;

        void Reset();

        bool IsVictoryFor(Player player) const;
        bool IsGridFull() const;

    private:
        void UpdateIsVictoryFor(U8 x, U8 y, Player player);
        void UpdateIsGridFull();

        std::array<Player, k_sizeGrid* k_sizeGrid> m_grid{ Player::Empty };
        bool m_isCrossVictory{ false };
        bool m_isNoughtVictory{ false };
        bool m_isGridFull{ false };
    };
}
