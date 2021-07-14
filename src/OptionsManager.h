#pragma once

#include "Utils.h"

namespace TicTacToe
{
    class OptionsManager
        : public NonCopyable
        , public NonMoveable
    {
    public:
        bool IsAI(Player player) const;

        void UpdateCrossState(int state);
        void UpdateNoughtState(int state);

    private:
        bool m_isCrossAI{ false };
        bool m_isNoughtAI{ false };
    };
}
