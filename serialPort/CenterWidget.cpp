#include "CenterWidget.h"

CenterWidget::CenterWidget(QWidget *parent) : QFrame(parent)
{
    serialWin = new serialWindow();
    STM32_ISP_Win = new STM32_ISP_window();

    stackWidget = new QStackedWidget();
    stackWidget->addWidget(serialWin);
    stackWidget->addWidget(STM32_ISP_Win);
    stackWidget->setCurrentIndex(0);

    mainLayout = new QGridLayout();
    mainLayout->addWidget(stackWidget, 0, 0);
    setLayout(mainLayout);
}
