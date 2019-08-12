#ifndef SERIALWINDOW_H
#define SERIALWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPlainTextEdit>

#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QRadioButton>

#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>


#define Time_out        10
#define Time_interval   250


class serialWindow : public QWidget
{
    Q_OBJECT
public:
    explicit serialWindow(QWidget *parent = 0);
    ~serialWindow();

    // 串口参数设置
    QLabel      *comLabel, *baudLabel, *dataBitLabel, *parityLabel, *stopBitLabel, *flowControlLabel;
    QComboBox   *comComboBox, *baudComboBox, *dataBitComboBox, *parityComboBox, *stopBitComboBox, *flowControlComboBox;

    // 串口接收
    QRadioButton    *stringRadioBtnRX, *hexRadioBtnRX;
    QPushButton     *recvPlainEditClearBtn;
    QCheckBox       *autoLineBreakCheckBox, *showTheTimeCheckBox;

    // 串口发送
    QRadioButton    *stringRadioBtnTX, *hexRadioBtnTX;
    QCheckBox       *repeatSendCheckBox, *sendDataShowCheckBox;
    QLabel          *repeatTimesLabel, *repeatTimeIntervalLabel;
    QSpinBox        *repeadTimesSpinBox, *repeatTimeIntervalSpinBox;
    QPushButton     *sendPlainEditClearBtn;

    //
    QPlainTextEdit  *serialReceivePlaintext, *serialSendPlaintext;
    QPushButton     *autoSearchComBtn, *openComBtn, *sendBtn;


    // 非界面变量 - 串口操作相关变量
    QTimer          *readTimer;
    QSerialPort     *serialPort;

private:
    bool            autoLineBreakFlag = true, repeatSendFlag = false, sendDataShow = false;
    bool            recvDataOutpoutWithHex = false, sendDataInputWithHex = false;
    QGroupBox       *serialParameterComGBox, *serialSendComBox, *serialReceiveComBox;
    QGridLayout     *serialMainLayout;

    // 功能相关函数，在serialPort.cpp文件中实现
public slots:
    void on_autoSearchComBtn_clicked(void);
    void on_openComBtn_clicked(void);
    void on_sendBtn_clicked(void);

    void on_recvPlainEditClearBtn_clicked(void);
    void on_sendPlainEditClearBtn_clicked(void);

    void on_stringRadioBtnRX_toggled(void);
    void on_stringRadioBtnTX_toggled(void);

    void receive_Data_From_serialPort(void);
    void on_autoLineBreakCheckBox_checked(void);
    void on_sendDataShowCheckBox_checked(void);
    void on_repeatSendCheckBox_checked(void);

    // 界面相关函数，在serialWindow.cpp文件中实现
private slots:
    void serialPortLayout(void);

    void serialParameterLayout(void);
    void serialReceiveLayout(void);
    void serialSendLayout(void);

signals:
};

#endif
