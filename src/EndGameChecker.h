#pragma once

#include "Utils.h"

namespace TicTacToe
{
    namespace EndGameChecker
    {
        bool IsVictoryFor(const Grid& grid, Player player);
        bool IsGridFull(const Grid& grid);
    }
}
