#pragma once

#include "Utils.h"

#include <utility>
#include <vector>

namespace TicTacToe
{
    class AIManager
        : public NonCopyable
    {
    public:
        static AIManager& Instance();

        std::vector<std::pair<U8, U8>> GetBestMoves();
        S8 CalcMin(const Map& map, const U8& depth);
        S8 CalcMax(const Map& map, const U8& depth);
    };
}
