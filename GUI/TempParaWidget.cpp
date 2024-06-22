#include "TempParaWidget.h"
#include "Model/TempPCTPackHandler.h"
#include "Model/PCTPackDistributor.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QThread>
TempParaWidget::TempParaWidget(QWidget *parent)
	: QWidget(parent)
{
	Temp_label = new QLabel("Temp", this);
	Temp_label->setObjectName("Temp_Title");
	Temp_value_label = new QLabel(QString("-- ℃"));
	Temp_value_label->setObjectName("Temp_Label");
	lead_status_label = new QLabel("STOP", this);
	lead_status_label->setObjectName("Lead_Label");
	lead_status_label->setStyleSheet("QLabel { color : red; }");
	initMainLayout();
	setObjectName("TempParaWidget");
	setMinimumSize(0, 0);
	initHandler();
}

TempParaWidget::~TempParaWidget()
{
	handler_thread->deleteLater();
	handler->deleteLater();
	delete Temp_label;
	delete Temp_value_label;
	delete lead_status_label;
	delete main_layout;
}

void TempParaWidget::connectPCTDistributorSignals(PCTPackDistributor* d)
{
	connect(d, &PCTPackDistributor::TEMP_PCT_DATA,
		handler, &TempPCTPackHandler::PCTPackHandleTask);
}

void TempParaWidget::onSerialPortOpened()
{
	para_status = TempParaStatus::RUN;
}

void TempParaWidget::initMainLayout()
{
	main_layout = new QVBoxLayout(this);
	main_layout->addWidget(Temp_label);
	main_layout->addWidget(Temp_value_label);
	main_layout->addWidget(lead_status_label);
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(10);
}

void TempParaWidget::initHandler()
{
	handler = new TempPCTPackHandler();
	handler_thread = new QThread();
	handler->moveToThread(handler_thread);
	handler_thread->start();

	connect(handler, &TempPCTPackHandler::updateValue, this, &TempParaWidget::onUpdateValue);
}

void TempParaWidget::onUpdateValue(TempPCTPackHandler::PCTPackValueID ID, qreal value)
{
	if (para_status == TempParaStatus::STOP) return;
	if(ID == TempPCTPackHandler::PCTPackValueID::LEAD_STATUS)
		updateLeadStatus((TempLeadStatus)value);
	else if (ID == TempPCTPackHandler::PCTPackValueID::PARA_VALUE)
		updateTempValue(value);
}

void TempParaWidget::updateTempValue(qreal value)
{
	TempValue = value;
	Temp_value_label->setText(QString::number(value,'f',1) + " ℃");
}

void TempParaWidget::updateLeadStatus(TempLeadStatus s)
{
	if (lead_status == s) return;
	if (s == TempLeadStatus::LeadOn)
	{
		lead_status_label->setText("Lead ON");
		lead_status_label->setStyleSheet("QLabel { color : rgb(80, 80, 80); }");
	}
	else
	{
		lead_status_label->setText("Lead OFF");
		lead_status_label->setStyleSheet("QLabel { color : red; }");
		Temp_value_label->setText("-- ℃");
	}
	lead_status = s;
}

void TempParaWidget::resetTempLabel()
{
	Temp_value_label->setText("-- ℃");
	lead_status_label->setText("STOP");
	lead_status_label->setStyleSheet("QLabel { color : red; }");
	lead_status = TempLeadStatus::LeadOff;
	para_status = TempParaStatus::STOP;
}

GenericPCTPackHandler* TempParaWidget::getPCTPackHandler()
{
	return handler;
}
