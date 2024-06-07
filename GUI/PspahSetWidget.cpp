#include "PspahSetWidget.h"
#include "GUI/ECGParaWidget.h"
#include "GUI/SpO2ParaWidget.h"
#include "GUI/TempParaWidget.h"
#include "Model/PCTPackDistributor.h"
#include "SerialPortSettingsWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QThread>

PspahSetWidget::PspahSetWidget(QWidget *parent)
	: QWidget(parent)
{
	setObjectName("PspahSetWidget");
	pasph_label = new QLabel(tr("PhysiologicalPara"), this);
	pasph_label->setObjectName("title_label");
	QFont font = pasph_label->font();
	font.setBold(true); // 设置字体加粗
	pasph_label->setFont(font);

	ecg_para_widget = new ECGParaWidget(this);
	spo2_para_widget = new SpO2ParaWidget(this);
	temp_para_widget = new TempParaWidget(this);
	initMainLayout();
	initThreadPool();
}

PspahSetWidget::~PspahSetWidget()
{
	delete pasph_label;
	delete ecg_para_widget;
	delete spo2_para_widget;
	delete temp_para_widget;
	delete main_layout;
}

void PspahSetWidget::initMainLayout()
{
	main_layout = new QVBoxLayout(this);
	main_layout->addWidget(pasph_label);
	main_layout->addWidget(ecg_para_widget);
	main_layout->addSpacing(50);
	main_layout->addWidget(spo2_para_widget);
	main_layout->addSpacing(50);
	main_layout->addWidget(temp_para_widget);
	main_layout->setContentsMargins(15, 15, 15, 15);
	main_layout->addStretch();
}

void PspahSetWidget::initThreadPool()
{
	//for (int i = 0; i < 3; i++)
	//{
	//	QThread* thread = new QThread(this);
	//	thread_pool.append(thread);
	//}
	//temp_para_widget->moveToThread(thread_pool[2]);
}

void PspahSetWidget::connectPCTDistributorSignals(PCTPackDistributor* d)
{
	temp_para_widget->connectPCTDistributorSignals(d);
	spo2_para_widget->connectPCTDistributorSignals(d);
	ecg_para_widget->connectPCTDistributorSignals(d);

	connect(d, &PCTPackDistributor::SYS_PCT_DATA,
		this, &PspahSetWidget::onSYS_PCT_DATA);
}

void PspahSetWidget::connectSerialPortSignals(SerialPortSettingsWidget* s)
{
	connect(s, &SerialPortSettingsWidget::serialPortOpened,
		ecg_para_widget, &ECGParaWidget::onSerialPortOpened);

	connect(s, &SerialPortSettingsWidget::serialPortOpened,
		temp_para_widget, &TempParaWidget::onSerialPortOpened);

	connect(s, &SerialPortSettingsWidget::serialPortOpened,
		spo2_para_widget, &SpO2ParaWidget::onSerialPortOpened);
}

ECGParaWidget* PspahSetWidget::getECGParaWidget()
{
	return ecg_para_widget;
}

SpO2ParaWidget* PspahSetWidget::getSpO2ParaWidget()
{
	return spo2_para_widget;
}

TempParaWidget* PspahSetWidget::getTempParaWidget()
{
	return temp_para_widget;
}

void PspahSetWidget::onSYS_PCT_DATA(StructPCTPackType pctdata)
{
	EnumPCTPackID s_id = (EnumPCTPackID)pctdata.packSecondId;
	if (s_id == EnumSysSecondID::DAT_RST)
	{
		//qDebug() << "SYS RET:" << (bool)pctdata.arrData[0];
		if (pctdata.arrData[0])startParaSetLabel();
		else resetParaSetLabel();
	}
}

void PspahSetWidget::startParaSetLabel()
{
	ecg_para_widget->onSerialPortOpened();
	spo2_para_widget->onSerialPortOpened();
	temp_para_widget->onSerialPortOpened();
}

void PspahSetWidget::resetParaSetLabel()
{
	ecg_para_widget->resetECGLabel();
	spo2_para_widget->resetSpO2Label();
	temp_para_widget->resetTempLabel();
}

void PspahSetWidget::onSerialPortClosed()
{
	resetParaSetLabel();
}