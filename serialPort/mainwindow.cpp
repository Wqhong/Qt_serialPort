#include "Mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("主界面"));
    setMinimumSize(800, 480);
    createAction();
    createToolBar();

    centerWidget = new CenterWidget(this);
    setCentralWidget(centerWidget);
}

//Action动作
void MainWindow::createAction()
{
    //转到第一个界面
    openStackWin[0] = new QAction(tr("串口功能"), this);
    openStackWin[0]->setShortcut(tr("Ctrl+Q"));
    openStackWin[0]->setStatusTip(tr("界面1"));
    connect(openStackWin[0], SIGNAL(triggered(bool)), this, SLOT(openSerialWin()));
    //转到第二个界面
    openStackWin[1] = new QAction(tr("ISP下载"), this);
    openStackWin[1]->setShortcut(tr("Ctrl+W"));
    openStackWin[1]->setStatusTip(tr("界面2"));
    connect(openStackWin[1], SIGNAL(triggered(bool)), this, SLOT(openSTM32_ISP_Win()));
}

//创建工具栏
void MainWindow::createToolBar()
{
    stackTool = addToolBar("工具栏");
    stackTool->addAction(openStackWin[0]);
    stackTool->addAction(openStackWin[1]);
}

//转到界面1槽函数
void MainWindow::openSerialWin()
{
    centerWidget->stackWidget->setCurrentIndex(0);
}

//转到界面2槽函数
void MainWindow::openSTM32_ISP_Win()
{
    centerWidget->stackWidget->setCurrentIndex(1);
}

MainWindow::~MainWindow()
{

}
