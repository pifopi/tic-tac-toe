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
        bool CheckFullRow(U8 x, Player player) const;
        bool CheckFullColumn(U8 y, Player player) const;
        bool CheckFullDiagonal(Player player) const;
        bool CheckFullAntediagonal(Player player) const;
        bool CheckFullLine(const std::array<Player, k_sizeGrid>& line, Player player) const;

        std::array<Player, k_sizeGrid* k_sizeGrid> m_grid{ Player::Empty };
        bool m_isCrossVictory{ false };
        bool m_isNoughtVictory{ false };
        bool m_isGridFull{ false };
    };
}
