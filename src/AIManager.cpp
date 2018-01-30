#include "AIManager.h"
#include "GameManager.h"

#include <algorithm>

namespace TicTacToe
{
    AIManager& AIManager::Instance()
    {
        static AIManager instance;
        return instance;
    }

    std::vector<std::pair<U8, U8>> AIManager::GetBestMoves()
    {
        auto& map = GameManager::Instance().GetMap();
        S8 max = std::numeric_limits<S8>::min();

        std::vector<std::pair<U8, U8>> bestMoves;

        for (U8 x = 0; x < 3; ++x)
        {
            for (U8 y = 0; y < 3; ++y)
            {
                if (map[x][y] == Player::Empty)
                {
                    auto mapCopy = map;
                    mapCopy[x][y] = GameManager::Instance().GetCurrentPlayer();

                    S8 calc = CalcMin(mapCopy, 1);
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

    S8 AIManager::CalcMin(const Map& map, const U8& depth)
    {
        if (GameManager::Instance().GetVictory(map, GameManager::Instance().GetCurrentPlayer()))
        {
            return std::numeric_limits<S8>::max() - depth;
        }
        else if (GameManager::Instance().GetVictory(map, GameManager::Instance().GetCurrentOpponent()))
        {
            return std::numeric_limits<S8>::min() + depth;
        }
        else if (GameManager::Instance().IsMapFull(map))
        {
            return depth;
        }

        S8 min = std::numeric_limits<S8>::max();
        for (U8 x = 0; x < 3; ++x)
        {
            for (U8 y = 0; y < 3; ++y)
            {
                if (map[x][y] == Player::Empty)
                {
                    auto mapCopy = map;
                    mapCopy[x][y] = GameManager::Instance().GetCurrentOpponent();
                    min = std::min(CalcMax(mapCopy, depth + 1), min);
                }
            }
        }
        return min;
    }

    S8 AIManager::CalcMax(const Map& map, const U8& depth)
    {
        if (GameManager::Instance().GetVictory(map, GameManager::Instance().GetCurrentPlayer()))
        {
            return std::numeric_limits<S8>::max() - depth;
        }
        else if (GameManager::Instance().GetVictory(map, GameManager::Instance().GetCurrentOpponent()))
        {
            return std::numeric_limits<S8>::min() + depth;
        }
        else if (GameManager::Instance().IsMapFull(map))
        {
            return depth;
        }

        S8 max = std::numeric_limits<S8>::min();
        for (U8 x = 0; x < 3; ++x)
        {
            for (U8 y = 0; y < 3; ++y)
            {
                if (map[x][y] == Player::Empty)
                {
                    auto mapCopy = map;
                    mapCopy[x][y] = GameManager::Instance().GetCurrentPlayer();
                    max = std::max(CalcMin(mapCopy, depth + 1), max);
                }
            }
        }
        return max;
    }
}
