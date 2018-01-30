#pragma once

#include "Utils.h"

#include <QIcon>

namespace TicTacToe
{
    class ImageManager
        : public NonCopyable
    {
    public:
        static ImageManager& Instance();

        const QIcon& GetPlayerImage(const Player& player) const;

    private:
        ImageManager();

        QIcon m_emptyIcon;
        QIcon m_crossIcon;
        QIcon m_noughtIcon;
    };
}
