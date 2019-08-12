#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "CenterWidget.h"

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QGridLayout>
#include <QMainWindow>
#include <QStackedWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    CenterWidget        *centerWidget;
    QGridLayout         *gridLayout;

    void createAction();                                //动作处理函数
    void createToolBar();                               //创建工具栏

private:
    QToolBar    *stackTool;                                //工具栏
    QAction     *openStackWin[2];

private slots:
    void openSerialWin();                                //点击状态栏的槽函数
    void openSTM32_ISP_Win();
};

#endif // MAINWINDOW_H
