#pragma once
#include <QWidget>
#include <Core/PasphMacros.h>
#include "Model/SerialPortModel.h"
#include <QSerialPort>
class QLabel;
class QComboBox;
class QFormLayout;
class QVBoxLayout;
class QHBoxLayout;
class PspahGenericButton;
class SerialPortInfoWidget;
class PCTPackDistributor;
class QThread;

class SerialPortSettingsWidget  : public QWidget
{
	Q_OBJECT
	P_Widget_PaintEventOverride
public:
	SerialPortSettingsWidget(QWidget *parent);
	~SerialPortSettingsWidget();
	QString getPortNumber();
	enum QSerialPort::BaudRate getBaudRate();
	enum QSerialPort::DataBits getDataBit();
	enum QSerialPort::StopBits getStopBit();
	enum QSerialPort::Parity getParityBit();
	void setSerialPortInfoWidget(SerialPortInfoWidget*);
	void connectSerialPortModelAndDistributor(PCTPackDistributor*);
signals:
	void serialPortOpened();
	void serialPortOpenError();
	void serialPortClosed();
	void seiralInfoPush(const QString&);
private:
	void initSelf();
	void initMainLayout();
	void initSerialPortModel();
	void updatePortNumberBox();

	void onSerialPortOpened();
	void onSerialPortOpenError();
	void onSerialPortClosed();
	SerialPortModel* serial_port_model{};
	SerialPortInfoWidget* serial_port_info_widget{};
	QVBoxLayout* main_layout{};

	QFormLayout* form_layout{};
	QComboBox* port_number_combobox{};
	QComboBox* baud_rate_combobox{};
	QComboBox* data_bit_combobox{};
	QComboBox* stop_bit_combobox{};
	QComboBox* parity_bit_combobox{};

	QHBoxLayout* title_layout{};
	QLabel* serial_port_settings_label{};
	PspahGenericButton* serial_port_open_button{};
	PspahGenericButton* serial_port_close_button{};

	QThread* serial_port_thread{};
};
