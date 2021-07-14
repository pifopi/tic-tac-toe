#include "Grid.h"

#include <algorithm>
#include <cassert>

namespace TicTacToe
{
    void Grid::Set(const U8 x, const U8 y, const Player player)
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

    bool Grid::CheckFullRow(const U8 x, const Player player) const
    {
        bool isFull = true;
        for (U8 i = 0; i < k_sizeGrid; ++i)
        {
            isFull &= player == Get(x, i);
        }
        return isFull;
    }

    bool Grid::CheckFullColumn(const U8 y, const Player player) const
    {
        bool isFull = true;
        for (U8 i = 0; i < k_sizeGrid; ++i)
        {
            isFull &= player == Get(i, y);
        }
        return isFull;
    }

    bool Grid::CheckFullDiagonal(const Player player) const
    {
        bool isFull = true;
        for (U8 i = 0; i < k_sizeGrid; ++i)
        {
            isFull &= player == Get(i, i);
        }
        return isFull;
    }

    bool Grid::CheckFullAntediagonal(const Player player) const
    {
        bool isFull = true;
        for (U8 i = 0; i < k_sizeGrid; ++i)
        {
            isFull &= player == Get(i, k_sizeGrid - 1 - i);
        }
        return isFull;
    }
}