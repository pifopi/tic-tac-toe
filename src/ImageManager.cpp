#include "ImageManager.h"

#include <cassert>

namespace TicTacToe
{
    ImageManager::ImageManager()
        : m_emptyIcon("White.png")
        , m_crossIcon("Cross.png")
        , m_noughtIcon("Nought.png")
    {

    }

    const QIcon& ImageManager::GetPlayerImage(const Player player) const
    {
        switch (player)
        {
        case Player::Empty:
            return m_emptyIcon;
        case Player::Cross:
            return m_crossIcon;
        case Player::Nought:
            return m_noughtIcon;
        default:
            assert(false);
            exit(EXIT_FAILURE);
        }
    }
}
