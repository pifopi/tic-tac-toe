#pragma once

#include "Utils.h"

#include <array>
#include <QWidget>

class QGridLayout;
class QPushButton;
class QSignalMapper;

namespace TicTacToe
{
    class MainWindow
        : public QWidget
        , public NonCopyable
    {
        Q_OBJECT
    public:
        static MainWindow& Instance();

        void UpdateButtons();
        void DisplayEndGame(const Player& player);

    private:
        MainWindow();
        ~MainWindow();

        QPushButton* m_showOptionsWindowButton;
        QSignalMapper* m_signalMapper;
        std::array<std::array<QPushButton*, 3>, 3> m_buttons;
        QGridLayout* m_layout;

        private slots:
        void SelectCase(const QString& text);
        void ShowOptionsWindow();
    };
}
