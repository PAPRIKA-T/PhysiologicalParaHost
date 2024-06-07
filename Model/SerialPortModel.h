#pragma once
#include <QObject>
class QSerialPort;
class QComboBox;
class SerialPortSettingsWidget;
class SerialPortInfoWidget;
class SerialPortScanner;

class SerialPortModel  : public QObject
{
	Q_OBJECT
public:
	SerialPortModel(QObject *parent = nullptr);
	~SerialPortModel();
	void setSerialPortSettingsWidget(SerialPortSettingsWidget*);
signals:
	void serialPortChanged();
	void serialPortOpened();
	void serialPortOpenError();
	void serialPortClosed();
	void transmitPCTData(const QString&);
	void seiralInfoPush(const QString&);
public slots:
	bool onOpenCurrentSerialPort();
	void onCloseCurrentSerialPort();
	void onBaudRateChanged(int);
	void onDataBitChanged(int);
	void onStopBitChanged(int);
	void onParityChanged(int);
	void onRXFormatChanged(int);
private:
	void setCurrentSerialPort();
	void ReadCurrentSerialData();
	void TransmitCurrentSerialData();
	void initSerialPort();
	QSerialPort* serial_port{};
	SerialPortScanner* serial_port_scanner{};
	SerialPortSettingsWidget* seria_port_settings_widget{};
	QString sp_Rx_buffer{};
	bool CurrentSerialPortOpened = false;
	bool RXFormatIsHex = true;
	bool TXFormatIsHex = false;
	bool IsReadCurrentSerialData = false;
};
