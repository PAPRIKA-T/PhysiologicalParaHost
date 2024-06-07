#include "SerialPortScanner.h"
#include <QTimer>
#include <QDebug>
#include <QSerialPort>

SerialPortScanner::SerialPortScanner(QObject *parent)
	: QObject(parent)
{
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();
    m_lastSerialPorts = serialPorts;
    // 每隔1秒钟重新扫描一次串口
    serial_scan_timer = new QTimer(this);
    connect(serial_scan_timer, &QTimer::timeout, this, &SerialPortScanner::scanSerialPorts);
}

SerialPortScanner::~SerialPortScanner()
{
    delete serial_scan_timer;
}

void SerialPortScanner::scannerStart()
{
    serial_scan_timer->start(500);
}

void SerialPortScanner::scannerStop()
{
    serial_scan_timer->stop();
}

void SerialPortScanner::scanSerialPorts()
{
    serial_scan_timer->stop();
    // 获取当前可用的串口信息列表
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();
    // 如果串口列表与上次不同，则打印新的串口信息
    if (m_lastSerialPorts.length() != serialPorts.length())
    {
        m_lastSerialPorts = serialPorts;
        emit serialPortsChanged();
    }
    serial_scan_timer->start(500);
}
