#pragma once

#include "Utils.h"

#include <QDialog>

class QCheckBox;
class QVBoxLayout;

namespace TicTacToe
{
    class OptionWindow
        : public QDialog
        , public NonCopyable
    {
        Q_OBJECT
    public:
        static OptionWindow& Instance();

    private:
        OptionWindow();

        QCheckBox* m_AICrossCheckBox;
        QCheckBox* m_AINoughtCheckBox;
        QVBoxLayout* m_layout;

        private slots:
        void AICross(const int& state);
        void AINought(const int& state);
    };
}
