#include "SerialPortModel.h"
#include "GUI/SerialPortSettingsWidget.h"
#include "GUI/SerialPortInfoWidget.h"
#include "SerialPortScanner.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QComboBox>
#include <QMessageBox>
#include <QTextEdit>
#include <QTimer>

SerialPortModel::SerialPortModel(QObject *parent)
	: QObject(parent)
{
    initSerialPort();
}

SerialPortModel::~SerialPortModel()
{
    serial_port_scanner->deleteLater();
	delete serial_port;
}

void SerialPortModel::setSerialPortSettingsWidget(SerialPortSettingsWidget* s)
{
	seria_port_settings_widget = s;
}

void SerialPortModel::onCloseCurrentSerialPort()
{
    if (!CurrentSerialPortOpened)return;
	serial_port->close();
	CurrentSerialPortOpened = false;
	emit serialPortClosed();
    emit seiralInfoPush(QString(tr("Serial Port Closed")));
    emit seiralInfoPush(QString("--------------------------------------------"));
}

void SerialPortModel::onBaudRateChanged(int)
{
    serial_port->setBaudRate(seria_port_settings_widget->getBaudRate());
}

void SerialPortModel::onDataBitChanged(int)
{
    serial_port->setDataBits(seria_port_settings_widget->getDataBit());
}

void SerialPortModel::onStopBitChanged(int)
{
    serial_port->setStopBits(seria_port_settings_widget->getStopBit());
}

void SerialPortModel::onParityChanged(int)
{
    serial_port->setParity(seria_port_settings_widget->getParityBit());
}

void SerialPortModel::onRXFormatChanged(int c)
{
    RXFormatIsHex = c;
    if (c)
    {
        emit seiralInfoPush(QString(tr("RXFormat HEX Checked")));
        emit seiralInfoPush(QString("--------------------------------------------"));
    }
    else
    {
        emit seiralInfoPush(QString(tr("RXFormat HEX UnChecked")));
        emit seiralInfoPush(QString("--------------------------------------------"));
    }
}

void SerialPortModel::setCurrentSerialPort()
{
	serial_port->setPortName(seria_port_settings_widget->getPortNumber());
	serial_port->setBaudRate(seria_port_settings_widget->getBaudRate());
	serial_port->setParity(seria_port_settings_widget->getParityBit());
	serial_port->setDataBits(seria_port_settings_widget->getDataBit());
	serial_port->setStopBits(seria_port_settings_widget->getStopBit());
}

void SerialPortModel::ReadCurrentSerialData()
{
    IsReadCurrentSerialData = true;
    QByteArray buffer = serial_port->readAll();
    QString Str;
    if (!buffer.isEmpty())
    {
        if (RXFormatIsHex)
        {
            //qDebug() << "buffer " << buffer;
            QString hexString = QString::fromLatin1(buffer.toHex());
            //添加空格
            for (int i = 2; i < hexString.length()+1; i += 3) {
                hexString.insert(i, ' ');
            }
            Str = hexString.toUpper();
            //qDebug() << "bufferHex:" << Str;
        }
        else
        {
            Str = buffer;
        }
        emit seiralInfoPush(Str);
        //qDebug()<<"sp_Rx_buffer: "<<sp_Rx_buffer;
        emit transmitPCTData(Str);
    }
    IsReadCurrentSerialData = false;
}

void SerialPortModel::TransmitCurrentSerialData()
{
    //QByteArray data{};
    //if (!CurrentSerialPortOpened)
    //{
    //    QMessageBox::warning(this, tr("Warning"),
    //        tr("Please Open Port First"), QMessageBox::Ok);
    //    return;
    //}

    //if (TXFormatIsHex)
    //{
    //    QString Str = ui->sendContentlineEdit->text();
    //    QStringList DataList = Str.split(" ");
    //    qDebug() << "DataList " << DataList;

    //    for (int i = 0; i < DataList.length(); i++)
    //    {
    //        bool ok;
    //        QString tempStr = DataList.at(i);
    //        if (tempStr != " " && tempStr != "")
    //        {
    //            qDebug() << "tempStr " << tempStr;
    //            data.append((char)tempStr.toInt(&ok, 16));
    //        }
    //    }
    //    qDebug() << "Send QByteArray  " << data;
    //    HiSerialPort->write(data);

    //    TXCount += data.size();
    //}
    //else
    //{
    //    QByteArray ba = ui->sendContentlineEdit->text().toLatin1();
    //    HiSerialPort->write(ba.data());
    //    TXCount += ba.size();
    //}
    //UpdateLCDNumber(1);
}

void SerialPortModel::initSerialPort()
{
    serial_port = new QSerialPort(this);
    serial_port_scanner = new SerialPortScanner(this);
    connect(serial_port_scanner, &SerialPortScanner::serialPortsChanged,
        this, &SerialPortModel::serialPortChanged);
    serial_port_scanner->scannerStart();
    connect(serial_port, &QSerialPort::readyRead,
        this, &SerialPortModel::ReadCurrentSerialData);
}

bool SerialPortModel::onOpenCurrentSerialPort()
{
    if (CurrentSerialPortOpened) 
    {
        emit seiralInfoPush(QString(tr("Serial Port Has Opened, return")));
        emit seiralInfoPush(QString("--------------------------------------------"));
        return false;
    }
	setCurrentSerialPort();
    if (serial_port->open(QIODevice::ReadWrite))
	{
        CurrentSerialPortOpened = true;
		emit serialPortOpened();
        emit seiralInfoPush(QString(tr("Serial Port Opened")));
        emit seiralInfoPush(QString("--------------------------------------------"));
        return true;
	}
	else
	{
        CurrentSerialPortOpened = false;
		emit serialPortOpenError();
        emit seiralInfoPush(QString(tr("Serial Port Opened Failed")));
        emit seiralInfoPush(QString("--------------------------------------------"));
        return false;
	}
}
