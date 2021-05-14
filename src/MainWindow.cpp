#include "MainWindow.h"

#include "GameManager.h"
#include "ImageManager.h"

#include <cassert>
#include <QBoxLayout>
#include <QMessageBox>
#include <QPushButton>

namespace TicTacToe
{
    namespace
    {
        constexpr U8 k_sizeButton{ 200 };
    }

    MainWindow::MainWindow(const Grid& grid, const ImageManager& imageManager, GameManager& gameManager)
    {
        for (auto& row : m_buttons)
        {
            for (auto& elem : row)
            {
                elem = new QPushButton();
            }
        }

        auto* vBoxLayout{ new QVBoxLayout() };
        for (U8 x = 0; x < k_sizeGrid; ++x)
        {
            auto* hBoxLayout{ new QHBoxLayout() };
            for (U8 y = 0; y < k_sizeGrid; ++y)
            {
                m_buttons[x][y]->setToolTip(QString("%1 | %2").arg(x).arg(y));
                m_buttons[x][y]->setIconSize(QSize(k_sizeButton, k_sizeButton));
                QObject::connect(m_buttons[x][y], &QPushButton::clicked, [x, y, &gameManager]() { gameManager.PlayAt(x, y); });
                hBoxLayout->addWidget(m_buttons[x][y]);
            }
            vBoxLayout->addLayout(hBoxLayout);
        }

        auto* showOptionsWindowButton{ new QPushButton("&Options") };
        QObject::connect(showOptionsWindowButton, &QPushButton::clicked, [&gameManager]() { gameManager.ShowOptionsWindow(); });
        vBoxLayout->addWidget(showOptionsWindowButton);

        setLayout(vBoxLayout);
        UpdateButtons(grid, imageManager);
    }

    void MainWindow::UpdateButtons(const Grid& grid, const ImageManager& imageManager)
    {
        for (U8 x = 0; x < k_sizeGrid; ++x)
        {
            for (U8 y = 0; y < k_sizeGrid; ++y)
            {
                m_buttons[x][y]->setIcon(imageManager.GetPlayerImage(grid[x][y]));
                if (grid[x][y] == Player::Empty)
                {
                    m_buttons[x][y]->setEnabled(true);
                }
                else
                {
                    m_buttons[x][y]->setEnabled(false);
                }
            }
        }
    }

    void MainWindow::DisplayEndGame(const Player player, GameManager& gameManager)
    {
        QString message;
        switch (player)
        {
        case Player::Cross:
            message = "Cross player (X) won this game.";
            break;
        case Player::Nought:
            message = "Nought player (O) won this game.";
            break;
        case Player::Empty:
            message = "Draw";
            break;
        default:
            assert(false);
            exit(EXIT_FAILURE);
        }

        switch (QMessageBox::question(this, "End of the game", message + " Would you like to play again ? ", QMessageBox::Yes | QMessageBox::No))
        {
        case QMessageBox::Yes:
            gameManager.Reset();
            break;
        case QMessageBox::No:
            exit(EXIT_SUCCESS);
        default:
            break;
        }
    }
}
