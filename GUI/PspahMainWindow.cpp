#include "PspahMainWindow.h"
#include "GUI/SerialPortSettingsWidget.h"
#include "GUI/PspahSetWidget.h"
#include "GUI/SerialPortInfoWidget.h"
#include "GUI/PspahWaveSetWidget.h"
#include "Model/PCTPackDistributor.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QThread>

PspahMainWindow::PspahMainWindow(QWidget* parent)
	: QWidget(parent)
{
	//设置窗口的图标和名称
	setWindowIcon(QIcon(":/PspahResource/ICON/HOST_ICON.svg"));
	setWindowTitle(tr("PhysiologicalParaHost"));
	setMinimumSize(500, 0);
	resize(1100, 700);
	initRightLayout();
	initLeftLayout();
	initMainLayout();
	transferSerialInfoWidget();
	initPCTPackDistributor();
	initSerialPortDistributorSignal();
	initSignals();
}

PspahMainWindow::~PspahMainWindow()
{
	PCTPackDistributor_hread->deleteLater();
	delete pct_pack_distributor;
	delete pspah_wave_set_widget;
	delete serial_port_settings_widget;
	delete pasph_set_widget;
	delete central_right_layout;

	delete serial_port_info_widget;
	delete central_left_layout;

	delete main_layout;
}

void PspahMainWindow::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
	central_widget->resize(size());
}

void PspahMainWindow::initMainLayout()
{
	central_widget = new QWidget(this);
	central_widget->setMinimumSize(MIN_WIDTH, MIN_HEIGHT);
	//设置主窗口的布局
	main_layout = new QHBoxLayout(central_widget);
	main_layout->addLayout(central_left_layout);
	main_layout->addLayout(central_right_layout);
	main_layout->setContentsMargins(2, 2, 2, 2);
	main_layout->setSpacing(5);
}

void PspahMainWindow::initSignals()
{
	connect(serial_port_settings_widget, &SerialPortSettingsWidget::serialPortClosed,
		pasph_set_widget, &PspahSetWidget::onSerialPortClosed);
	pspah_wave_set_widget->connectPspahSetWidgetSignals(pasph_set_widget);
}

void PspahMainWindow::initRightLayout()
{
	//设置右侧窗口的布局
	central_right_layout = new QVBoxLayout();
	pasph_set_widget = new PspahSetWidget(this);
	pasph_set_widget->setFixedWidth(250);
	central_right_layout->addWidget(pasph_set_widget);
	central_right_layout->setContentsMargins(0, 0, 0, 0);
	central_right_layout->setSpacing(0);
	//central_right_layout->addStretch();
}

void PspahMainWindow::initLeftLayout()
{
	//设置左侧窗口的布局
	central_left_layout = new QVBoxLayout();
	left_bottom_layout = new QHBoxLayout();
	pspah_wave_set_widget = new PspahWaveSetWidget(this);
	central_left_layout->addWidget(pspah_wave_set_widget);
	central_left_layout->addLayout(left_bottom_layout);
	central_left_layout->setContentsMargins(0, 0, 0, 0);

	serial_port_settings_widget = new SerialPortSettingsWidget(this);
	serial_port_settings_widget->setFixedSize(300,200);
	serial_port_info_widget = new SerialPortInfoWidget(this);
	serial_port_info_widget->setMinimumWidth(300);
	serial_port_info_widget->setFixedHeight(200);
	left_bottom_layout->addWidget(serial_port_settings_widget);
	left_bottom_layout->addWidget(serial_port_info_widget);
	left_bottom_layout->setContentsMargins(0, 0, 0, 0);
	left_bottom_layout->setSpacing(0);
}

void PspahMainWindow::transferSerialInfoWidget()
{
	serial_port_settings_widget->setSerialPortInfoWidget(serial_port_info_widget);
}

void PspahMainWindow::initPCTPackDistributor()
{
	pct_pack_distributor = new PCTPackDistributor();
	serial_port_settings_widget->connectSerialPortModelAndDistributor(pct_pack_distributor);
	PCTPackDistributor_hread = new QThread();
	pct_pack_distributor->moveToThread(PCTPackDistributor_hread);
	PCTPackDistributor_hread->start();
}

void PspahMainWindow::initSerialPortDistributorSignal()
{
	pasph_set_widget->connectPCTDistributorSignals(pct_pack_distributor);
	pasph_set_widget->connectSerialPortSignals(serial_port_settings_widget);
}
