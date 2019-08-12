#include "Mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("串口助手-Wqhong");
    w.show();

    return a.exec();
}
