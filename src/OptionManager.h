#pragma once

#include "Utils.h"

namespace TicTacToe
{
    class OptionManager
        : public NonCopyable
    {
    public:
        static OptionManager& Instance();

        const bool& GetAI(const Player& player) const;
        void SetAI(const Player& player, const bool& value);

    private:
        OptionManager();

        bool m_AICross;
        bool m_AINought;
    };
}
