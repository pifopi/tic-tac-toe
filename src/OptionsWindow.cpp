#include "OptionsWindow.h"

#include "GameManager.h"
#include "OptionsManager.h"

#include <QBoxLayout>
#include <QCheckBox>

namespace TicTacToe
{
    OptionsWindow::OptionsWindow(OptionsManager& optionsManager, GameManager& gameManager)
    {
        auto* AICrossCheckBox{ new QCheckBox("Make the Cross player AI controlled") };
        QObject::connect(AICrossCheckBox, &QCheckBox::stateChanged, [&optionsManager](int state) { optionsManager.UpdateCrossState(state); });

        auto* AINoughtCheckBox{ new QCheckBox("Make the Nought player AI controlled") };
        QObject::connect(AINoughtCheckBox, &QCheckBox::stateChanged, [&optionsManager](int state) { optionsManager.UpdateNoughtState(state); });

        auto* layout{ new QVBoxLayout() };
        layout->addWidget(AICrossCheckBox);
        layout->addWidget(AINoughtCheckBox);
        setLayout(layout);

        QObject::connect(this, &QDialog::finished, [&gameManager](int) { gameManager.PlayAITurnIfNeeded(); });
    }
}
