#include "ECGParaWidget.h"
#include "Model/PCTPackDistributor.h"
#include "Core/PasphGenericOperation.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QThread>

ECGParaWidget::ECGParaWidget(QWidget *parent)
	: QWidget(parent)
{
	ECG_label = new QLabel("ECG", this);
	ECG_label->setObjectName("ECG_Title");
	ECG_value_label = new QLabel("--- bpm", this);
	ECG_value_label->setObjectName("ECG_Label");
	lead_status_label = new QLabel("STOP", this);
	lead_status_label->setObjectName("Lead_Label");
	lead_status_label->setStyleSheet("QLabel { color : red; }");
	initMainLayout();
	initHandler();
	setObjectName("ECGParaWidget");
	setMinimumSize(0, 0);
}

ECGParaWidget::~ECGParaWidget()
{
	handler_thread->deleteLater();
	handler->deleteLater();
	delete ECG_label;
	delete ECG_value_label;
	delete lead_status_label;
	delete main_layout;
}

void ECGParaWidget::updateECGValue(int value)
{
	ECG_value_label->setText(QString::number(value) + " bpm");
}

void ECGParaWidget::updateLeadStatus(ECGLeadStatus s)
{
	if (lead_status == s) return;
	if (s == ECGLeadStatus::LeadOn)
	{
		lead_status_label->setText("Lead ON");
		lead_status_label->setStyleSheet("QLabel { color : rgb(80, 80, 80); }");
	}
	else
	{
		ECG_value_label->setText("--- bpm");
		lead_status_label->setText("Lead OFF");
		lead_status_label->setStyleSheet("QLabel { color : red; }");
	}
	lead_status = s;
}

void ECGParaWidget::connectPCTDistributorSignals(PCTPackDistributor* d)
{
	connect(d, &PCTPackDistributor::ECG_PCT_DATA,
		handler, &EcgPCTPackHandler::PCTPackHandleTask);
}

void ECGParaWidget::resetECGLabel()
{
	ECG_value_label->setText("--- bpm");
	lead_status_label->setText("STOP");
	lead_status_label->setStyleSheet("QLabel { color : red; }");
	para_status = ECGParaStatus::STOP;
	lead_status = ECGLeadStatus::NONE;
}

EcgPCTPackHandler* ECGParaWidget::getPCTPackHandler()
{
	return handler;
}

void ECGParaWidget::initMainLayout()
{
	main_layout = new QVBoxLayout(this);
	main_layout->addWidget(ECG_label);
	main_layout->addWidget(ECG_value_label);
	main_layout->addWidget(lead_status_label);
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(10);
}

void ECGParaWidget::initHandler()
{
	handler = new EcgPCTPackHandler();
	handler_thread = new QThread();
	handler->moveToThread(handler_thread);
	handler_thread->start();

	connect(handler, &EcgPCTPackHandler::updateValue, this, &ECGParaWidget::onUpdateValue);
}

void ECGParaWidget::onUpdateValue(EcgPCTPackHandler::PCTPackValueID ID, qreal value)
{
	if (para_status == ECGParaStatus::STOP) return;
	if (ID == EcgPCTPackHandler::PCTPackValueID::LEAD_STATUS) {
		updateLeadStatus((ECGLeadStatus)value);
	}
	else if (ID == EcgPCTPackHandler::PCTPackValueID::PARA_VALUE)
		updateECGValue(value);
}

void ECGParaWidget::onSerialPortOpened()
{
	//qDebug() << "ECGPara Thread:" << thread();
	para_status = ECGParaStatus::RUN;
}
