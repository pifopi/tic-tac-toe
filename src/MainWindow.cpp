#include "GameManager.h"
#include "ImageManager.h"
#include "MainWindow.h"
#include "OptionWindow.h"

#include <cassert>
#include <QGridLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QSignalMapper>

namespace TicTacToe
{
    MainWindow& MainWindow::Instance()
    {
        static MainWindow instance;
        return instance;
    }

    void MainWindow::UpdateButtons()
    {
        auto& map = GameManager::Instance().GetMap();

        for (U8 x = 0; x < 3; ++x)
        {
            for (U8 y = 0; y < 3; ++y)
            {
                m_buttons[x][y]->setIcon(ImageManager::Instance().GetPlayerImage(map[x][y]));
                if (map[x][y] == Player::Empty)
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

    void MainWindow::DisplayEndGame(const Player& player)
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
                GameManager::Instance().Reset();
                break;
            case QMessageBox::No:
                exit(EXIT_SUCCESS);
            default:
                break;
        }
    }

    MainWindow::MainWindow()
        : m_showOptionsWindowButton(new QPushButton("&Options"))
        , m_signalMapper(new QSignalMapper)
        , m_layout(new QGridLayout)
    {
        for (auto& row : m_buttons)
        {
            for (auto& elem : row)
            {
                elem = new QPushButton();
            }
        }

        for (U8 x = 0; x < 3; ++x)
        {
            for (U8 y = 0; y < 3; ++y)
            {
                m_buttons[x][y]->setToolTip(QString("%1 | %2").arg(x).arg(y));
                m_buttons[x][y]->setIconSize(QSize(200, 200));
                QObject::connect(m_buttons[x][y], SIGNAL(clicked()), m_signalMapper, SLOT(map()));
                m_signalMapper->setMapping(m_buttons[x][y], QString("%1%2").arg(x).arg(y));
                m_layout->addWidget(m_buttons[x][y], x, y);
            }
        }
        QObject::connect(m_signalMapper, SIGNAL(mapped(QString)), this, SLOT(SelectCase(QString)));

        QObject::connect(m_showOptionsWindowButton, SIGNAL(clicked()), this, SLOT(ShowOptionsWindow()));

        m_layout->addWidget(m_showOptionsWindowButton, 4, 0, 1, 3);

        setLayout(m_layout);
        UpdateButtons();
    }

    MainWindow::~MainWindow()
    {
        delete m_signalMapper;
    }

    void MainWindow::SelectCase(const QString& text)
    {
        U8 xy = text.toUInt();
        U8 y = xy % 10;
        U8 x = (xy - y) / 10;

        GameManager::Instance().PlayAt(x, y);
    }

    void MainWindow::ShowOptionsWindow()
    {
        OptionWindow::Instance().exec();
    }
}
