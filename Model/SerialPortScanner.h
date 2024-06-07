#pragma once
#include <QObject>
#include <QSerialPortInfo>

class SerialPortScanner : public QObject
{
	Q_OBJECT
public:
	SerialPortScanner(QObject *parent = nullptr);
	~SerialPortScanner();
	void scannerStart();
	void scannerStop();
signals:
	void serialPortsChanged();
private:
	void scanSerialPorts();
	QTimer* serial_scan_timer{};
	QList<QSerialPortInfo> m_lastSerialPorts{};
};
