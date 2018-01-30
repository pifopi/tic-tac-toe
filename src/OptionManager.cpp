#include "GameManager.h"
#include "OptionManager.h"

#include <cassert>
#include <cstdlib>

namespace TicTacToe
{
    OptionManager& OptionManager::Instance()
    {
        static OptionManager instance;
        return instance;
    }

    const bool& OptionManager::GetAI(const Player& player) const
    {
        switch (player)
        {
            case Player::Cross:
                return m_AICross;
            case Player::Nought:
                return m_AINought;
            default:
                assert(false);
                exit(EXIT_FAILURE);
        }
    }

    void OptionManager::SetAI(const Player& player, const bool& value)
    {
        switch (player)
        {
            case Player::Cross:
                m_AICross = value;
                break;
            case Player::Nought:
                m_AINought = value;
                break;
            default:
                assert(false);
                exit(EXIT_FAILURE);
        }

        if (value == true && player == GameManager::Instance().GetCurrentPlayer())
        {
            GameManager::Instance().PlayAITurn();
        }
    }

    OptionManager::OptionManager()
        : m_AICross(false)
        , m_AINought(false)
    {

    }
}
