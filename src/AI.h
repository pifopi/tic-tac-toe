#pragma once

#include "Utils.h"

#include <vector>

namespace TicTacToe
{
    namespace AI
    {
        //one grid copy is intended
        std::vector<std::pair<U8, U8>> GetBestMoves(Grid grid, Player currentPlayer, Player opponentPlayer);
    }
}
