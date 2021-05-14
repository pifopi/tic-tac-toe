#pragma once

#include "Utils.h"

#include <array>
#include <QWidget>

class QPushButton;

namespace TicTacToe
{
    class GameManager;
    class ImageManager;

    class MainWindow
        : public QWidget
    {
        Q_OBJECT
    public:
        MainWindow(const Grid& grid, const ImageManager& imageManager, GameManager& gameManager);

        void UpdateButtons(const Grid& grid, const ImageManager& imageManager);
        void DisplayEndGame(Player player, GameManager& gameManager);

    private:
        std::array<std::array<QPushButton*, k_sizeGrid>, k_sizeGrid> m_buttons;
    };
}
