#include "OptionsManager.h"

#include <cassert>
#include <QCheckBox>

namespace TicTacToe
{
    bool OptionsManager::IsAI(const Player player) const
    {
        switch (player)
        {
        case Player::Cross:
            return m_isCrossAI;
        case Player::Nought:
            return m_isNoughtAI;
        default:
            assert(false);
            exit(EXIT_FAILURE);
        }
    }

    void OptionsManager::UpdateCrossState(const int state)
    {
        switch (state)
        {
        case Qt::Unchecked:
            m_isCrossAI = false;
            break;
        case Qt::Checked:
            m_isCrossAI = true;
            break;
        default:
            break;
        }
    }

    void OptionsManager::UpdateNoughtState(const int state)
    {
        switch (state)
        {
        case Qt::Unchecked:
            m_isNoughtAI = false;
            break;
        case Qt::Checked:
            m_isNoughtAI = true;
            break;
        default:
            break;
        }
    }
}
