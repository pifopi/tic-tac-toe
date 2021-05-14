#include "AI.h"

#include "EndGameChecker.h"

#include <algorithm>

namespace TicTacToe
{
    namespace AI
    {
        S8 CalcMin(Grid& grid, Player currentPlayer, Player opponentPlayer, U8 depth);
        S8 CalcMax(Grid& grid, Player currentPlayer, Player opponentPlayer, U8 depth);

        S8 CalcMin(Grid& grid, const Player currentPlayer, const Player opponentPlayer, const U8 depth)
        {
            if (EndGameChecker::IsVictoryFor(grid, currentPlayer))
            {
                return std::numeric_limits<S8>::max() - depth;
            }
            else if (EndGameChecker::IsVictoryFor(grid, opponentPlayer))
            {
                return std::numeric_limits<S8>::min() + depth;
            }
            else if (EndGameChecker::IsGridFull(grid))
            {
                return depth;
            }

            S8 min = std::numeric_limits<S8>::max();
            for (U8 x = 0; x < k_sizeGrid; ++x)
            {
                for (U8 y = 0; y < k_sizeGrid; ++y)
                {
                    if (grid[x][y] == Player::Empty)
                    {
                        grid[x][y] = opponentPlayer;
                        min = std::min(CalcMax(grid, currentPlayer, opponentPlayer, depth + 1), min);
                        grid[x][y] = Player::Empty;
                    }
                }
            }
            return min;
        }

        S8 CalcMax(Grid& grid, const Player currentPlayer, const Player opponentPlayer, const U8 depth)
        {
            if (EndGameChecker::IsVictoryFor(grid, currentPlayer))
            {
                return std::numeric_limits<S8>::max() - depth;
            }
            else if (EndGameChecker::IsVictoryFor(grid, opponentPlayer))
            {
                return std::numeric_limits<S8>::min() + depth;
            }
            else if (EndGameChecker::IsGridFull(grid))
            {
                return depth;
            }

            S8 max = std::numeric_limits<S8>::min();
            for (U8 x = 0; x < k_sizeGrid; ++x)
            {
                for (U8 y = 0; y < k_sizeGrid; ++y)
                {
                    if (grid[x][y] == Player::Empty)
                    {
                        grid[x][y] = currentPlayer;
                        max = std::max(CalcMin(grid, currentPlayer, opponentPlayer, depth + 1), max);
                        grid[x][y] = Player::Empty;
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
                    if (grid[x][y] == Player::Empty)
                    {
                        grid[x][y] = currentPlayer;
                        S8 calc = CalcMin(grid, currentPlayer, opponentPlayer, 1);
                        grid[x][y] = Player::Empty;

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
