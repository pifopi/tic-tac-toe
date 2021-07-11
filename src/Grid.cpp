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
            //checks the row
            {
                std::array<Player, k_sizeGrid> row;
                for (U8 i = 0; i < k_sizeGrid; ++i)
                {
                    row[i] = Get(x, i);
                }
                if (std::all_of(begin(row), end(row), [player](const Player p)
                    {
                        return player == p;
                    }))
                {
                    isVictory = true;
                }
            }

            //checks the column
            {
                std::array<Player, k_sizeGrid> column;
                for (U8 i = 0; i < k_sizeGrid; ++i)
                {
                    column[i] = Get(i, y);
                }
                if (std::all_of(begin(column), end(column), [player](const Player p)
                    {
                        return player == p;
                    }))
                {
                    isVictory = true;
                }
            }

            //check the diagonal if needed
            if (x == y)
            {
                std::array<Player, k_sizeGrid> diagonal;
                for (U8 i = 0; i < k_sizeGrid; ++i)
                {
                    diagonal[i] = Get(i, i);
                }
                if (std::all_of(begin(diagonal), end(diagonal), [player](const Player p)
                    {
                        return player == p;
                    }))
                {
                    isVictory = true;
                }

            }

            //check the antediagonal if needed
            if (x == k_sizeGrid - 1 - y)
            {
                std::array<Player, k_sizeGrid> anteDiagonal;
                for (U8 i = 0; i < k_sizeGrid; ++i)
                {
                    anteDiagonal[i] = Get(i, k_sizeGrid - 1 - i);
                }
                if (std::all_of(begin(anteDiagonal), end(anteDiagonal), [player](const Player p)
                    {
                        return player == p;
                    }))
                {
                    isVictory = true;
                }
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
}