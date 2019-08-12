#include "SerialWindow.h"

#include <QDebug>

#include <QChar>
#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QTextCodec>

#include <string>
#include <QTextBlock>   // 用于转换发送面板的数据
#include <QTextDocument>


// 自动搜索并设置端口号
void serialWindow::on_autoSearchComBtn_clicked(void)
{
    QStringList comList;

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            comList << info.portName();
            serial.close();
        }
    }

    if(comList.size() != 0)
    {
        comComboBox->clear();
        comComboBox->addItems(comList);
    }
}

// 打开串口并初始化按钮和文字
void serialWindow::on_openComBtn_clicked(void)
{
    if(openComBtn->text() == "打开串口")
    {
        serialPort = new QSerialPort;   // 关闭时使用了deleteLater()，这里不判断NULL的情况

        serialPort->setPortName(comComboBox->currentText());
        if(serialPort->open(QIODevice::ReadWrite))             //打开串口
        {
            serialPort->setBaudRate(baudComboBox->currentText().toInt());
            switch(dataBitComboBox->currentIndex())
            {
                case 0: serialPort->setDataBits(QSerialPort::Data8);break;
                case 1: serialPort->setDataBits(QSerialPort::Data7);break;
                case 2: serialPort->setDataBits(QSerialPort::Data6);break;
                case 3: serialPort->setDataBits(QSerialPort::Data5);break;
                default:break;
            }
            switch(parityComboBox->currentIndex())
            {
                case 0: serialPort->setParity(QSerialPort::NoParity);break;
                case 1: serialPort->setParity(QSerialPort::OddParity);break;
                case 2: serialPort->setParity(QSerialPort::EvenParity);break;
                default:break;
            }
            switch(stopBitComboBox->currentIndex())
            {
                case 0: serialPort->setStopBits(QSerialPort::OneStop);break;
                case 1: serialPort->setStopBits(QSerialPort::TwoStop);break;
                default:break;
            }
            // 缺少流控

            comComboBox->setEnabled(false);
            baudComboBox->setEnabled(false);
            dataBitComboBox->setEnabled(false);
            stopBitComboBox->setEnabled(false);
            parityComboBox->setEnabled(false);
            flowControlComboBox->setEnabled(false);

            openComBtn->setText("关闭串口");
            sendBtn->setEnabled(true);

            if(readTimer != NULL) readTimer->start(Time_interval);
        }
        else
        {
            // 串口打开失败
        }
    }
    else
    {
        serialPort->clear();
        serialPort->close();
        serialPort->deleteLater();

        comComboBox->setEnabled(true);
        baudComboBox->setEnabled(true);
        dataBitComboBox->setEnabled(true);
        stopBitComboBox->setEnabled(true);
        parityComboBox->setEnabled(true);
        flowControlComboBox->setEnabled(true);

        openComBtn->setText("打开串口");
        sendBtn->setEnabled(false);

        readTimer->stop();
    }
}


void serialWindow::on_sendBtn_clicked(void)
{
    QByteArray tmp;

    QTextDocument *document = serialSendPlaintext->document();
    for(QTextBlock block = document->begin(); block != document->end(); block = block.next())
    {
        if(!sendDataInputWithHex)
        {
            tmp.append(block.text().toUtf8());
        }
        else    // 将字符串表示的16进制转换为对应的字符串
        {
            QString s = "";
            std::string s1 = block.text().toUtf8().trimmed().toStdString() + ' ';
            for(unsigned int i = 0, num = 0; i < s1.length(); i++)
            {
                if(s1[i] != ' ')
                {
                    if(num >= 256) num = 0;

                    if(s1[i] <= '9' && s1[i] >= '0') num = num * 16 + (s1[i] - '0');
                    else if(s1[i] <= 'Z' && s1[i] >= 'A') num = num * 16 + (s1[i] - 'A' + 10);
                    else if(s1[i] <= 'z' && s1[i] >= 'a') num = num * 16 + (s1[i] - 'a' + 10);
                    else num = 0;
                }
                else
                {
                    s += num;
                    num = 0;
                }
            }

            tmp.append(s);
        }
    }

    if(tmp != NULL)
    {
        if(sendDataShow)
        {
            QString str = "发送数据：";
            if(!recvDataOutpoutWithHex) serialReceivePlaintext->appendPlainText(str + tmp);
            else
            {
                tmp = tmp.toHex();
                for(int i = 0; i < tmp.length() / 2; i++)
                {
                    str += tmp.mid(i * 2, 2) + " ";
                }
                serialReceivePlaintext->appendPlainText(str);
            }
        }
        serialPort->write(tmp);
    }
}


void serialWindow::on_recvPlainEditClearBtn_clicked(void)
{
    serialReceivePlaintext->clear();
}


void serialWindow::on_sendPlainEditClearBtn_clicked(void)
{
    serialSendPlaintext->clear();
}


void serialWindow::on_stringRadioBtnRX_toggled(void)
{
    if(stringRadioBtnRX->isChecked()) recvDataOutpoutWithHex = false;
    else recvDataOutpoutWithHex = true;
}


void serialWindow::on_stringRadioBtnTX_toggled(void)
{
    if(stringRadioBtnTX->isChecked()) sendDataInputWithHex = false;
    else
    {
        QByteArray tmp, tmp2;
        QTextDocument *document = serialSendPlaintext->document();
        for(QTextBlock block = document->begin(); block != document->end(); block = block.next())
        {
            tmp.append(block.text().toLatin1().toHex());
        }
        serialSendPlaintext->clear();

        for(int i = 0; i < tmp.length() / 2; i++)
        {
            tmp2 += tmp.mid(i * 2, 2) + " ";
        }
        serialSendPlaintext->appendPlainText(tmp2);

        sendDataInputWithHex = true;
    }
}


void serialWindow::receive_Data_From_serialPort(void)
{
    // 串口读取接收代码
    QByteArray buf;
    buf = serialPort->readAll();
    if(!buf.isEmpty())
    {
        QString strUnicode = "";

        if(!autoLineBreakFlag){
            strUnicode = serialReceivePlaintext->toPlainText();
            serialReceivePlaintext->clear();
        }

        if(sendDataShow) strUnicode += "接收数据：";
        if(!recvDataOutpoutWithHex)
        {
            QTextCodec* gb2312Codec = QTextCodec::codecForName("gb2312");

            strUnicode += gb2312Codec->toUnicode(buf);
        }
        else
        {
            buf = buf.toHex();
            for(int i = 0; i < buf.length() / 2; i++)
            {
                strUnicode += buf.mid(i * 2, 2) + " ";
            }
        }

        serialReceivePlaintext->appendPlainText(strUnicode);
    }
    buf.clear();
}


void serialWindow::on_autoLineBreakCheckBox_checked(void)
{
    if(autoLineBreakCheckBox->isChecked()) autoLineBreakFlag = true;
    else autoLineBreakFlag = false;
}


void serialWindow::on_sendDataShowCheckBox_checked(void)
{
    if(sendDataShowCheckBox->isChecked()) sendDataShow = true;
    else sendDataShow = false;
}


void serialWindow::on_repeatSendCheckBox_checked(void)
{
    if(repeatSendCheckBox->isChecked()) repeatSendFlag = true;
    else   = false;
}
