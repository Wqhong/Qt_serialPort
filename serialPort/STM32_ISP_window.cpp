#include "STM32_ISP_window.h"

#include <QString>
#include <QFileDialog>


STM32_ISP_window::STM32_ISP_window(QWidget *parent) : QWidget(parent)
{
    ispLabel = new QLabel("this is ISP window!");
    openFileBtn = new QPushButton("打开");
    gridLayout = new QGridLayout;
    gridLayout->addWidget(openFileBtn, 0, 0);
    gridLayout->addWidget(ispLabel, 0, 1);
    setLayout(gridLayout);

    connect(openFileBtn, SIGNAL(clicked(bool)), this, SLOT(on_openFileBtn_clicked()));
}

void STM32_ISP_window::on_openFileBtn_clicked()
{
    QString filePath = QFileDialog:: getOpenFileName(this, tr("打开文件"), tr(""), tr("文本文件(*.txt)"));
    if(filePath == "") return;
    ispLabel->setText(filePath);
}


STM32_ISP_window::~STM32_ISP_window()
{

}
