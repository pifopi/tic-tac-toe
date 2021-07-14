#include "Grid.h"

#include <algorithm>
#include <cassert>

namespace TicTacToe
{
    void Grid::Set(U8 x, U8 y, Player player)
    {
        m_grid[x * k_sizeGrid + y] = player;

        UpdateIsVictoryFor(x, y, player);
        UpdateIsGridFull();
    }

    Player Grid::Get(const U8 x, const U8 y) const
    {
        return m_grid[x * k_sizeGrid + y];
    }

    void Grid::Reset()
    {
        for (auto& elem : m_grid)
        {
            elem = Player::Empty;
        }
        m_isCrossVictory = false;
        m_isNoughtVictory = false;
        m_isGridFull = false;
    }

    bool Grid::IsVictoryFor(const Player player) const
    {
        switch (player)
        {
        case Player::Cross:
            return m_isCrossVictory;
        case Player::Nought:
            return m_isNoughtVictory;
        default:
            assert(false);
            exit(EXIT_FAILURE);
        }
    }

    bool Grid::IsGridFull() const
    {
        return m_isGridFull;
    }

    void Grid::UpdateIsVictoryFor(const U8 x, const U8 y, const Player player)
    {
        bool isVictory = false;
        if (player != Player::Empty)
        {
            isVictory |= CheckFullRow(x, player);
            isVictory |= CheckFullColumn(y, player);

            //check the diagonal if needed
            if (x == y)
            {
                isVictory |= CheckFullDiagonal(player);
            }

            //check the antediagonal if needed
            if (x == k_sizeGrid - 1 - y)
            {
                isVictory |= CheckFullAntediagonal(player);
            }
        }

        switch (player)
        {
        case Player::Empty:
            m_isCrossVictory = false;
            m_isNoughtVictory = false;
            break;
        case Player::Cross:
            m_isCrossVictory = isVictory;
            m_isNoughtVictory = false;
            break;
        case Player::Nought:
            m_isCrossVictory = false;
            m_isNoughtVictory = isVictory;
            break;
        }
    }

    void Grid::UpdateIsGridFull()
    {
        for (auto elem : m_grid)
        {
            if (elem == Player::Empty)
            {
                m_isGridFull = false;
                return;
            }
        }
        m_isGridFull = true;
    }

    bool Grid::CheckFullRow(const U8 x, Player player) const
    {
        std::array<Player, k_sizeGrid> row;
        for (U8 i = 0; i < k_sizeGrid; ++i)
        {
            row[i] = Get(x, i);
        }
        return CheckFullLine(row, player);
    }

    bool Grid::CheckFullColumn(const U8 y, Player player) const
    {
        std::array<Player, k_sizeGrid> column;
        for (U8 i = 0; i < k_sizeGrid; ++i)
        {
            column[i] = Get(i, y);
        }
        return CheckFullLine(column, player);
    }

    bool Grid::CheckFullDiagonal(Player player) const
    {
        std::array<Player, k_sizeGrid> diagonal;
        for (U8 i = 0; i < k_sizeGrid; ++i)
        {
            diagonal[i] = Get(i, i);
        }
        return CheckFullLine(diagonal, player);
    }

    bool Grid::CheckFullAntediagonal(Player player) const
    {
        std::array<Player, k_sizeGrid> anteDiagonal;
        for (U8 i = 0; i < k_sizeGrid; ++i)
        {
            anteDiagonal[i] = Get(i, k_sizeGrid - 1 - i);
        }
        return CheckFullLine(anteDiagonal, player);
    }

    bool Grid::CheckFullLine(const std::array<Player, k_sizeGrid>& line, const Player player) const
    {
        return std::all_of(begin(line), end(line), [player](const Player p)
        {
            return player == p;
        });
    }
}