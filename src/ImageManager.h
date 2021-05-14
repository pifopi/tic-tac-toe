#pragma once

#include "Utils.h"

#include <QIcon>

namespace TicTacToe
{
    class ImageManager
    {
    public:
        ImageManager();
        const QIcon& GetPlayerImage(Player player) const;

    private:
        QIcon m_emptyIcon;
        QIcon m_crossIcon;
        QIcon m_noughtIcon;
    };
}
