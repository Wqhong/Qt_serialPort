#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include "SerialWindow.h"
#include "STM32_ISP_window.h"

#include <QTimer>
#include <QWidget>
#include <QFrame>
#include <QGridLayout>
#include <QStackedWidget>


//#define Time_out        10
//#define Time_interval   250


class CenterWidget : public QFrame
{
public:
    CenterWidget(QWidget *parent = nullptr);
    serialWindow        *serialWin;
    STM32_ISP_window    *STM32_ISP_Win;
    QStackedWidget      *stackWidget;
    QGridLayout         *mainLayout;

    QTimer              *readTimer;         // 定时读取串口数据
};

#endif // CENTERWIDGET_H
