#ifndef STM32_ISP_WINDOW_H
#define STM32_ISP_WINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class STM32_ISP_window : public QWidget
{
    Q_OBJECT
public:
    explicit STM32_ISP_window(QWidget *parent = 0);
    ~STM32_ISP_window();

private:
    QLabel*         ispLabel;
    QPushButton*    openFileBtn;
    QGridLayout*    gridLayout;

signals:

public slots:
    void on_openFileBtn_clicked();
};

#endif // STM32_ISP_WINDOW_H
