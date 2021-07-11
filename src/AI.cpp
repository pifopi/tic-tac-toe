#include "AI.h"

#include "Grid.h"

#include <algorithm>

namespace TicTacToe
{
    namespace AI
    {
        S8 CalcMin(Grid& grid, Player currentPlayer, Player opponentPlayer, U8 depth);
        S8 CalcMax(Grid& grid, Player currentPlayer, Player opponentPlayer, U8 depth);

        S8 CalcMin(Grid& grid, const Player currentPlayer, const Player opponentPlayer, const U8 depth)
        {
            if (grid.IsVictoryFor(currentPlayer))
            {
                return std::numeric_limits<S8>::max() - depth;
            }
            else if (grid.IsVictoryFor(opponentPlayer))
            {
                return std::numeric_limits<S8>::min() + depth;
            }
            else if (grid.IsGridFull())
            {
                return depth;
            }

            S8 min = std::numeric_limits<S8>::max();
            for (U8 x = 0; x < k_sizeGrid; ++x)
            {
                for (U8 y = 0; y < k_sizeGrid; ++y)
                {
                    if (grid.Get(x, y) == Player::Empty)
                    {
                        grid.Set(x, y, opponentPlayer);
                        min = std::min(CalcMax(grid, currentPlayer, opponentPlayer, depth + 1), min);
                        grid.Set(x, y, Player::Empty);
                    }
                }
            }
            return min;
        }

        S8 CalcMax(Grid& grid, const Player currentPlayer, const Player opponentPlayer, const U8 depth)
        {
            if (grid.IsVictoryFor(currentPlayer))
            {
                return std::numeric_limits<S8>::max() - depth;
            }
            else if (grid.IsVictoryFor(opponentPlayer))
            {
                return std::numeric_limits<S8>::min() + depth;
            }
            else if (grid.IsGridFull())
            {
                return depth;
            }

            S8 max = std::numeric_limits<S8>::min();
            for (U8 x = 0; x < k_sizeGrid; ++x)
            {
                for (U8 y = 0; y < k_sizeGrid; ++y)
                {
                    if (grid.Get(x,  y) == Player::Empty)
                    {
                        grid.Set(x, y, currentPlayer);
                        max = std::max(CalcMin(grid, currentPlayer, opponentPlayer, depth + 1), max);
                        grid.Set(x, y, Player::Empty);
                    }
                }
            }
            return max;
        }

        std::vector<std::pair<U8, U8>> GetBestMoves(Grid grid, const Player currentPlayer, const Player opponentPlayer)
        {
            S8 max = std::numeric_limits<S8>::min();

            std::vector<std::pair<U8, U8>> bestMoves;

            for (U8 x = 0; x < k_sizeGrid; ++x)
            {
                for (U8 y = 0; y < k_sizeGrid; ++y)
                {
                    if (grid.Get(x, y) == Player::Empty)
                    {
                        grid.Set(x, y, currentPlayer);
                        S8 calc = CalcMin(grid, currentPlayer, opponentPlayer, 1);
                        grid.Set(x, y, Player::Empty);

                        if (calc > max)
                        {
                            max = calc;
                            bestMoves.clear();
                            bestMoves.push_back(std::make_pair(x, y));
                        }
                        else if (calc == max)
                        {
                            bestMoves.push_back(std::make_pair(x, y));
                        }
                    }
                }
            }
            return bestMoves;
        }
    }
}
