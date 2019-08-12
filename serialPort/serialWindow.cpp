#include "SerialWindow.h"

#include <QGroupBox>
#include <QStringList>


serialWindow::serialWindow(QWidget *parent) : QWidget(parent)
{
    serialPortLayout();
    setLayout(serialMainLayout);

    readTimer = new QTimer(this);

    connect(readTimer,SIGNAL(timeout()),this,SLOT(receive_Data_From_serialPort()));
    connect(autoSearchComBtn, SIGNAL(clicked(bool)), this, SLOT(on_autoSearchComBtn_clicked()));
    connect(openComBtn, SIGNAL(clicked(bool)), this, SLOT(on_openComBtn_clicked()));
    connect(sendBtn, SIGNAL(clicked(bool)), this, SLOT(on_sendBtn_clicked()));

    connect(recvPlainEditClearBtn, SIGNAL(clicked(bool)), this, SLOT(on_recvPlainEditClearBtn_clicked()));
    connect(sendPlainEditClearBtn, SIGNAL(clicked(bool)), this, SLOT(on_sendPlainEditClearBtn_clicked()));

    connect(stringRadioBtnRX, SIGNAL(toggled(bool)), this, SLOT(on_stringRadioBtnRX_toggled()));
    connect(stringRadioBtnTX, SIGNAL(toggled(bool)), this, SLOT(on_stringRadioBtnTX_toggled()));
    connect(autoLineBreakCheckBox, SIGNAL(toggled(bool)), this, SLOT(on_autoLineBreakCheckBox_checked()));
    connect(sendDataShowCheckBox, SIGNAL(toggled(bool)), this, SLOT(on_sendDataShowCheckBox_checked()));
    connect(repeatSendCheckBox, SIGNAL(toggled(bool)), this, SLOT(on_repeatSendCheckBox_checked()));
}


void serialWindow::serialPortLayout(void)
{
    serialParameterLayout();
    serialReceiveLayout();
    serialSendLayout();

    sendBtn = new QPushButton("发    送");
    sendBtn->setEnabled(false);
    openComBtn = new QPushButton("打开串口");
    autoSearchComBtn = new QPushButton("自动搜索");

    serialSendPlaintext = new QPlainTextEdit;
    serialReceivePlaintext = new QPlainTextEdit;
    serialReceivePlaintext->setReadOnly(true);

    serialMainLayout = new QGridLayout();
    serialMainLayout->addWidget(serialParameterComGBox, 0, 0, 3, 1);
    serialMainLayout->addWidget(serialReceiveComBox, 3, 0, 3, 1);
    serialMainLayout->addWidget(serialSendComBox, 6, 0, 3, 1);
    serialMainLayout->addWidget(serialReceivePlaintext, 0, 1, 6, 3);
    serialMainLayout->addWidget(serialSendPlaintext, 6, 1, 3, 2);

    serialMainLayout->addWidget(autoSearchComBtn, 6, 3, 1, 1);
    serialMainLayout->addWidget(openComBtn, 7, 3, 1, 1);
    serialMainLayout->addWidget(sendBtn, 8, 3, 1, 1);

    serialMainLayout->setColumnStretch(0, 1);
    serialMainLayout->setColumnStretch(1, 3);
}

void serialWindow::serialParameterLayout(void)
{
    comLabel = new QLabel("串口");
    comComboBox = new QComboBox;
    baudLabel = new QLabel("波特率");
    baudComboBox = new QComboBox;
    dataBitLabel = new QLabel("数据位");
    dataBitComboBox = new QComboBox;
    parityLabel = new QLabel("校验位");
    parityComboBox = new QComboBox;
    stopBitLabel = new QLabel("停止位");
    stopBitComboBox = new QComboBox;
    flowControlLabel = new QLabel("流控制");
    flowControlComboBox = new QComboBox;

    QStringList comList;
    comList << "COM1" << "COM2" << "COM3" << "COM4" << "COM5" << "COM6"
            << "COM7" << "COM8" << "COM9" << "COM10";
    comComboBox->addItems(comList);
    QStringList baudList;
    baudList <<"1200"<<"2400"<<"4800"<<"9600"<<"19200"<<"38400"
             <<"57600"<<"115200"<<"128000"<<"256000";
    baudComboBox->addItems(baudList);
    baudComboBox->setCurrentIndex(7);   // 设置默认波特率
    dataBitComboBox->addItem("8");
    dataBitComboBox->addItem("7");
    dataBitComboBox->addItem("6");
    dataBitComboBox->addItem("5");
    parityComboBox->addItem("无");
    parityComboBox->addItem("奇");
    parityComboBox->addItem("偶");
    stopBitComboBox->addItem("1");
    stopBitComboBox->addItem("2");
    flowControlComboBox->addItem("NONE");
    flowControlComboBox->addItem("RTS/CTS");
    flowControlComboBox->addItem("XON/XOFF");

    QGridLayout *comLayout = new QGridLayout;
    comLayout->addWidget(comLabel,0,0);
    comLayout->addWidget(comComboBox,0,1);
    comLayout->addWidget(baudLabel,1,0);
    comLayout->addWidget(baudComboBox,1,1);
    comLayout->addWidget(dataBitLabel,2,0);
    comLayout->addWidget(dataBitComboBox,2,1);
    comLayout->addWidget(parityLabel,3,0);
    comLayout->addWidget(parityComboBox,3,1);
    comLayout->addWidget(stopBitLabel,4,0);
    comLayout->addWidget(stopBitComboBox,4,1);
    comLayout->addWidget(flowControlLabel,5,0);
    comLayout->addWidget(flowControlComboBox,5,1);
    comLayout->setColumnStretch(0,1);
    comLayout->setColumnStretch(1,2);
    comLayout->setRowStretch(0,0);

    serialParameterComGBox = new QGroupBox("串口设置");
    serialParameterComGBox->setLayout(comLayout);
}

void serialWindow::serialReceiveLayout(void)
{
    stringRadioBtnRX = new QRadioButton("字符串");
    hexRadioBtnRX = new QRadioButton("Hex");
    stringRadioBtnRX->setChecked(true);

    autoLineBreakCheckBox = new QCheckBox("自动换行");
    autoLineBreakCheckBox->setChecked(true);
    showTheTimeCheckBox = new QCheckBox("显示时间");
    sendDataShowCheckBox = new QCheckBox("显示发送");
    recvPlainEditClearBtn = new QPushButton("清除接收");

    QGridLayout *recvParameterLayout = new QGridLayout;
    recvParameterLayout->addWidget(stringRadioBtnRX, 0, 0);
    recvParameterLayout->addWidget(hexRadioBtnRX, 0, 1);
    recvParameterLayout->addWidget(autoLineBreakCheckBox, 1, 0);
    recvParameterLayout->addWidget(showTheTimeCheckBox, 1, 1);
    recvParameterLayout->addWidget(sendDataShowCheckBox, 2, 0);
    recvParameterLayout->addWidget(recvPlainEditClearBtn, 2, 1);

    serialReceiveComBox = new QGroupBox("接收设置");
    serialReceiveComBox->setLayout(recvParameterLayout);
}

void serialWindow::serialSendLayout(void)
{
    stringRadioBtnTX = new QRadioButton("字符串");
    hexRadioBtnTX = new QRadioButton("Hex");
    stringRadioBtnTX->setChecked(true);

    repeatSendCheckBox = new QCheckBox("重复发送");
    repeatTimesLabel = new QLabel("重复次数");
    repeadTimesSpinBox = new QSpinBox;
    repeatTimeIntervalLabel = new QLabel("时间间隔");
    repeatTimeIntervalSpinBox = new QSpinBox;
    sendPlainEditClearBtn = new QPushButton("清除发送");

    QGridLayout *sendParameterLayout = new QGridLayout;
    sendParameterLayout->addWidget(stringRadioBtnTX, 0, 0);
    sendParameterLayout->addWidget(hexRadioBtnTX, 0, 1);
    sendParameterLayout->addWidget(repeatTimesLabel, 1, 0);
    sendParameterLayout->addWidget(repeadTimesSpinBox, 1, 1);
    sendParameterLayout->addWidget(repeatTimeIntervalLabel, 2, 0);
    sendParameterLayout->addWidget(repeatTimeIntervalSpinBox, 2, 1);
    sendParameterLayout->addWidget(repeatSendCheckBox, 3, 0);
    sendParameterLayout->addWidget(sendPlainEditClearBtn, 3, 1);

    serialSendComBox = new QGroupBox("发送设置");
    serialSendComBox->setLayout(sendParameterLayout);
}

serialWindow::~serialWindow()
{

}
