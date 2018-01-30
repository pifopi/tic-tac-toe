#include "OptionManager.h"
#include "OptionWindow.h"

#include <QBoxLayout>
#include <QCheckBox>

namespace TicTacToe
{
    OptionWindow& OptionWindow::Instance()
    {
        static OptionWindow instance;
        return instance;
    }

    OptionWindow::OptionWindow()
        : m_AICrossCheckBox(new QCheckBox("Make the Cross player AI controlled"))
        , m_AINoughtCheckBox(new QCheckBox("Make the Nought player AI controlled"))
        , m_layout(new QVBoxLayout)
    {
        m_AICrossCheckBox->setChecked(OptionManager::Instance().GetAI(Player::Cross));
        QObject::connect(m_AICrossCheckBox, SIGNAL(stateChanged(int)), this, SLOT(AICross(int)));

        m_AINoughtCheckBox->setChecked(OptionManager::Instance().GetAI(Player::Nought));
        QObject::connect(m_AINoughtCheckBox, SIGNAL(stateChanged(int)), this, SLOT(AINought(int)));

        m_layout->addWidget(m_AICrossCheckBox);
        m_layout->addWidget(m_AINoughtCheckBox);

        setLayout(m_layout);
    }

    void OptionWindow::AICross(const int& state)
    {
        switch (state)
        {
            case Qt::Unchecked:
                OptionManager::Instance().SetAI(Player::Cross, false);
                break;
            case Qt::Checked:
                OptionManager::Instance().SetAI(Player::Cross, true);
                break;
            default:
                break;
        }
    }

    void OptionWindow::AINought(const int& state)
    {
        switch (state)
        {
            case Qt::Unchecked:
                OptionManager::Instance().SetAI(Player::Nought, false);
                break;
            case Qt::Checked:
                OptionManager::Instance().SetAI(Player::Nought, true);
                break;
            default:
                break;
        }
    }
}
