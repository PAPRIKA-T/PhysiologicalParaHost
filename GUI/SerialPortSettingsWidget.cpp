#include "SerialPortSettingsWidget.h"
#include "PspahToolButton.h"
#include "SerialPortInfoWidget.h"
#include "Model/PCTPackDistributor.h"
#include <QLabel>
#include <QComboBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QDebug>
#include <QCheckBox>
#include <QThread>
#include <QLineEdit>

SerialPortSettingsWidget::SerialPortSettingsWidget(QWidget *parent)
	: QWidget(parent)
{
	initSelf();
	initSerialPortModel();
	initMainLayout();
}

SerialPortSettingsWidget::~SerialPortSettingsWidget()
{
	serial_port_thread->deleteLater();
	serial_port_model->deleteLater();
	delete title_layout;
	delete form_layout;
	delete main_layout;
}

QString SerialPortSettingsWidget::getPortNumber()
{
	QStringList parts = port_number_combobox->currentText().split(' ');
	return QString(parts[0]);
}

enum QSerialPort::BaudRate SerialPortSettingsWidget::getBaudRate()
{

	bool ok;
	enum QSerialPort::BaudRate ret {};
	switch (baud_rate_combobox->currentText().toLong(&ok, 10))
	{
	case 1200:
		ret = QSerialPort::Baud1200;
		break;
	case 2400:
		ret = QSerialPort::Baud2400;
		break;
	case 4800:
		ret = QSerialPort::Baud4800;
		break;
	case 9600:
		ret = QSerialPort::Baud9600;
		break;
	case 19200:
		ret = QSerialPort::Baud19200;
		break;
	case 38400:
		ret = QSerialPort::Baud38400;
		break;
	case 57600:
		ret = QSerialPort::Baud57600;
		break;
	case 115200:
		ret = QSerialPort::Baud115200;
		break;
	default:
		ret = (QSerialPort::BaudRate)NULL;
		break;
	}
	return ret;
}

enum QSerialPort::DataBits SerialPortSettingsWidget::getDataBit()
{
	QString CurrentDataBits = data_bit_combobox->currentText();
	if (CurrentDataBits == "5")      return QSerialPort::Data5;
	else if (CurrentDataBits == "6") return QSerialPort::Data6;
	else if (CurrentDataBits == "7") return QSerialPort::Data7;
	else if (CurrentDataBits == "8") return QSerialPort::Data8;
	return (QSerialPort::DataBits)NULL;
}

enum QSerialPort::StopBits SerialPortSettingsWidget::getStopBit()
{
	QString CurrentStopBits = stop_bit_combobox->currentText();
	if (CurrentStopBits == "1")        return QSerialPort::OneStop;
	else if (CurrentStopBits == "2")   return QSerialPort::TwoStop;
	return (QSerialPort::StopBits)NULL;
}

enum QSerialPort::Parity SerialPortSettingsWidget::getParityBit()
{
	QString CurrentParityBit = parity_bit_combobox->currentText();
	if (CurrentParityBit == "N")      return QSerialPort::NoParity;
	else if (CurrentParityBit == "O")  return QSerialPort::OddParity;
	else if (CurrentParityBit == "E") return QSerialPort::EvenParity;
	return QSerialPort::NoParity;
}

void SerialPortSettingsWidget::setSerialPortInfoWidget(SerialPortInfoWidget* s)
{
	serial_port_info_widget = s;
	connect(this, &SerialPortSettingsWidget::seiralInfoPush,
		serial_port_info_widget, &SerialPortInfoWidget::onSeiralInfoPush);
	connect(serial_port_model, &SerialPortModel::seiralInfoPush,
		serial_port_info_widget, &SerialPortInfoWidget::onSeiralInfoPush);
	connect(s->getHexDisplayCheckbox(), &QCheckBox::checkStateChanged,
		serial_port_model, &SerialPortModel::onRXFormatChanged);
	s->getHexDisplayCheckbox()->setChecked(true);

	updatePortNumberBox();
}

void SerialPortSettingsWidget::connectSerialPortModelAndDistributor(PCTPackDistributor* d)
{
	connect(serial_port_model, &SerialPortModel::transmitPCTData,
		d, &PCTPackDistributor::UnPackPCTData);
}

void SerialPortSettingsWidget::initSelf()
{
	setObjectName("SerialPortSettingsWidget");
	serial_port_settings_label = new QLabel(tr("SP Settings"), this);
	serial_port_settings_label->setObjectName("title_label");
	QFont font = serial_port_settings_label->font();
	font.setBold(true); // 设置字体加粗
	serial_port_settings_label->setFont(font);
	port_number_combobox = new QComboBox(this);
	//BuadRate
	baud_rate_combobox = new QComboBox(this);
	baud_rate_combobox->setFixedWidth(70);
	QStringList baudList{};
	baudList << "4800" << "9600" << "19200" << 
		"38400" << "57600" << "115200";
	baud_rate_combobox->addItems(baudList);
	baud_rate_combobox->setCurrentIndex(5);
	//DataBit
	data_bit_combobox = new QComboBox(this);
	data_bit_combobox->setFixedWidth(40);
	QStringList dataBitList{};
	dataBitList << "5" << "6" << "7" << "8";
	data_bit_combobox->addItems(dataBitList);
	data_bit_combobox->setCurrentIndex(3);
	//StopBit
	stop_bit_combobox = new QComboBox(this);
	stop_bit_combobox->setFixedWidth(40);
	stop_bit_combobox->addItem("1");
	stop_bit_combobox->addItem("2");
	//ParityBit
	parity_bit_combobox = new QComboBox(this);
	parity_bit_combobox->setFixedWidth(40);
	parity_bit_combobox->addItem("N");
	parity_bit_combobox->addItem("O");
	parity_bit_combobox->addItem("E");

	serial_port_open_button = new PspahToolButton(this);
	serial_port_open_button->setCustomTooltip(tr("Open SP"));
	serial_port_open_button->setIcon(QIcon(":/PspahResource/ICON/GreenPoint.png"));
	serial_port_close_button = new PspahToolButton(this);
	serial_port_close_button->setCustomTooltip(tr("Close SP"));
	serial_port_close_button->setIcon(QIcon(":/PspahResource/ICON/RedPoint.png"));
}

void SerialPortSettingsWidget::initMainLayout()
{
	main_layout = new QVBoxLayout(this);
	title_layout = new QHBoxLayout();
	form_layout = new QFormLayout();
	form_layout->addRow(QStringLiteral("Port Num:"), port_number_combobox);
	form_layout->addRow(QStringLiteral("Baud Rate:"), baud_rate_combobox);
	form_layout->addRow(QStringLiteral("Data Bit:"), data_bit_combobox);
	form_layout->addRow(QStringLiteral("Stop Bit:"), stop_bit_combobox);
	form_layout->addRow(QStringLiteral("Parity bit:"), parity_bit_combobox);
	form_layout->setContentsMargins(0, 0, 0, 0);
	form_layout->setHorizontalSpacing(10);

	//title_layout->addWidget(hex_display_label);
	//title_layout->addWidget(hex_display_checkbox);
	title_layout->addWidget(serial_port_settings_label);
	title_layout->addWidget(serial_port_open_button);
	title_layout->addWidget(serial_port_close_button);
	title_layout->setContentsMargins(0, 0, 0, 0);

	main_layout->addLayout(title_layout);
	main_layout->addLayout(form_layout);
	main_layout->setContentsMargins(10, 0, 5, 10);
}

void SerialPortSettingsWidget::initSerialPortModel()
{
	serial_port_model = new SerialPortModel();
	connect(serial_port_model, &SerialPortModel::serialPortChanged,
		this, &SerialPortSettingsWidget::updatePortNumberBox);

	connect(serial_port_model, &SerialPortModel::serialPortOpened,
		this, &SerialPortSettingsWidget::serialPortOpened);
	connect(serial_port_model, &SerialPortModel::serialPortOpenError,
		this, &SerialPortSettingsWidget::serialPortOpenError);
	connect(serial_port_model, &SerialPortModel::serialPortClosed,
		this, &SerialPortSettingsWidget::serialPortClosed);

	connect(serial_port_model, &SerialPortModel::serialPortOpened,
		this, &SerialPortSettingsWidget::onSerialPortOpened);
	connect(serial_port_model, &SerialPortModel::serialPortOpenError,
		this, &SerialPortSettingsWidget::onSerialPortOpenError);
	connect(serial_port_model, &SerialPortModel::serialPortClosed,
		this, &SerialPortSettingsWidget::onSerialPortClosed);

	serial_port_model->setSerialPortSettingsWidget(this);

	connect(baud_rate_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged),
		serial_port_model, &SerialPortModel::onBaudRateChanged);
	connect(data_bit_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged),
		serial_port_model, &SerialPortModel::onDataBitChanged);
	connect(stop_bit_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged),
		serial_port_model, &SerialPortModel::onStopBitChanged);
	connect(parity_bit_combobox, QOverload<int>::of(&QComboBox::currentIndexChanged),
		serial_port_model, &SerialPortModel::onParityChanged);

	connect(serial_port_open_button, &QPushButton::clicked, serial_port_model, &SerialPortModel::onOpenCurrentSerialPort);
	connect(serial_port_close_button, &QPushButton::clicked, serial_port_model, &SerialPortModel::onCloseCurrentSerialPort);

	//qDebug() << "SerialPortSettingsWidget Thread:" << thread();
	serial_port_thread = new QThread();
	serial_port_model->moveToThread(serial_port_thread);
	serial_port_thread->start();
}

void SerialPortSettingsWidget::updatePortNumberBox()
{
	emit seiralInfoPush(QString(tr("scan Serial Port...")));
	emit seiralInfoPush(QString("--------------------------------------------"));

	port_number_combobox->clear();
	foreach(const QSerialPortInfo & info, QSerialPortInfo::availablePorts())
	{
		QSerialPort ser;
		ser.setPort(info);
		port_number_combobox->addItem(info.portName() + " " + info.description());
		emit seiralInfoPush(QString("Name        : " + info.portName() + ""));
		emit seiralInfoPush(QString("Description : " + info.description() + ""));
		emit seiralInfoPush(QString("Manufacturer: " + info.manufacturer() + ""));
		//serial_port_info_widget->SeiralInfoPush(QString("isBusy()    : " + 
		//	PasphGenericOperation::SwapBool2QSting(info.isBusy() + "\n")));
		ser.close();
		emit seiralInfoPush(QString("--------------------------------------------"));
	}
	port_number_combobox->update();
}

void SerialPortSettingsWidget::onSerialPortOpened()
{
	port_number_combobox->setEnabled(false);
	port_number_combobox->setStyleSheet("QComboBox{color:red;}");
}

void SerialPortSettingsWidget::onSerialPortOpenError()
{

}

void SerialPortSettingsWidget::onSerialPortClosed()
{
	port_number_combobox->setEnabled(true);
	port_number_combobox->setStyleSheet("QComboBox{color:#000000;}");
}
