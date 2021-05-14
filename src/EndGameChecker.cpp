#include "EndGameChecker.h"

#include <algorithm>

namespace TicTacToe
{
    namespace EndGameChecker
    {
        bool IsVictoryFor(const Grid& grid, const Player player)
        {
            std::array<Line, 2 * k_sizeGrid + 2> checks;

            //checks the rows
            for (U8 i = 0; i < k_sizeGrid; ++i)
            {
                Line row{};
                for (U8 j = 0; j < k_sizeGrid; ++j)
                {
                    row[j] = grid[i][j];
                }
                checks[i] = row;
            }

            //checks the columns
            for (U8 i = 0; i < k_sizeGrid; ++i)
            {
                Line column{};
                for (U8 j = 0; j < k_sizeGrid; ++j)
                {
                    column[j] = grid[j][i];
                }
                checks[i + k_sizeGrid] = column;
            }

            //check the diagonal
            {
                Line diagonal{};
                for (U8 i = 0; i < k_sizeGrid; ++i)
                {
                    diagonal[i] = grid[i][i];
                }
                checks[2 * k_sizeGrid] = diagonal;
            }

            //check the antediagonal
            {
                Line anteDiagonal{};
                for (U8 i = 0; i < k_sizeGrid; ++i)
                {
                    anteDiagonal[i] = grid[i][k_sizeGrid - 1 - i];
                }
                checks[2 * k_sizeGrid + 1] = anteDiagonal;
            }

            if (std::any_of(begin(checks), end(checks), [player](const Line& lineToCheck)
                {
                    return std::all_of(begin(lineToCheck), end(lineToCheck), [player](const Player i) { return i == player; });
                }))
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool IsGridFull(const Grid& grid)
        {
            for (const auto& row : grid)
            {
                for (const auto elem : row)
                {
                    if (elem == Player::Empty)
                    {
                        return false;
                    }
                }
            }
            return true;
        }
    }
}