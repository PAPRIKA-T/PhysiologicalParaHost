#include "SpO2ParaWidget.h"
#include "Core/PasphGenericOperation.h"
#include "Model/PCTPackDistributor.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QThread>

SpO2ParaWidget::SpO2ParaWidget(QWidget *parent)
	: QWidget(parent)
{
	setObjectName("SpO2ParaWidget");
	setMinimumSize(0, 0);
	initSelf();
	initMainLayout();
	initHandler();
}

SpO2ParaWidget::~SpO2ParaWidget()
{
	handler_thread->deleteLater();
	handler->deleteLater();
	delete SpO2_label;
	delete SpO2_value_label;
	//delete PR_label;
	//delete PI_label;
	delete lead_status_label;
	delete main_layout;
}

void SpO2ParaWidget::updateSpO2Value(qreal value)
{
	SpO2_value_label->setText(QString::number(value, 'f', 2) + " %");
}

void SpO2ParaWidget::updatePRValue(int value)
{
	//PR_label->setText("PR " + QString::number(value) + " bpm");
}

void SpO2ParaWidget::updatePIValue(qreal value)
{
	//PI_label->setText("PI " + QString::number(value, 'f', 1) + " %");
}

void SpO2ParaWidget::updateLeadStatus(SpO2LeadStatus s)
{
	if (lead_status == s) return;
	if (s == SpO2LeadStatus::LeadOn)
	{
		lead_status_label->setText("Lead ON");
		lead_status_label->setStyleSheet("QLabel { color : rgb(80, 80, 80); }");
	}
	else
	{
		lead_status_label->setText("Lead OFF");
		lead_status_label->setStyleSheet("QLabel { color : red; }");
		SpO2_value_label->setText("---- %");
		//PR_label->setText("PR --- bpm");
		//PI_label->setText("PI -- %");
	}
	lead_status = s;
}

void SpO2ParaWidget::initHandler()
{
	handler = new SpO2PCTPackHandler();
	handler_thread = new QThread();
	handler->moveToThread(handler_thread);
	handler_thread->start();

	connect(handler, &SpO2PCTPackHandler::updateValue, this, &SpO2ParaWidget::onUpdateValue);
}

void SpO2ParaWidget::onUpdateValue(SpO2PCTPackHandler::PCTPackValueID ID, qreal value)
{
	if (para_status == SpO2ParaStatus::STOP) return;
	if (ID == SpO2PCTPackHandler::PCTPackValueID::LEAD_STATUS)
		updateLeadStatus((SpO2LeadStatus)value);
	else if (ID == SpO2PCTPackHandler::PCTPackValueID::PARA_VALUE)
		updateSpO2Value(value);
}

void SpO2ParaWidget::resetSpO2Label()
{
	SpO2_value_label->setText("---- %");
	//PR_label->setText("PR --- bpm");
	//PI_label->setText("PI -- %");
	lead_status_label->setText("STOP");
	lead_status_label->setStyleSheet("QLabel { color : red; }");
	para_status = SpO2ParaStatus::STOP;
	lead_status = SpO2LeadStatus::NONE;
}

void SpO2ParaWidget::connectPCTDistributorSignals(PCTPackDistributor* d)
{
	connect(d, &PCTPackDistributor::SPO2_PCT_DATA,
		handler, &SpO2PCTPackHandler::PCTPackHandleTask);
}

SpO2PCTPackHandler* SpO2ParaWidget::getPCTPackHandler()
{
	return handler;
}

void SpO2ParaWidget::initSelf()
{
	SpO2_label = new QLabel("SpO2", this);
	SpO2_label->setObjectName("SpO2_Title");
	SpO2_value_label = new QLabel("---- %", this);
	SpO2_value_label->setObjectName("SpO2_Label");
	//PR_label = new QLabel("PR --- bpm", this);
	//PR_label->setObjectName("SpO2_Label");
	//PI_label = new QLabel("PI -- %", this);
	//PI_label->setObjectName("SpO2_Label");
	lead_status_label = new QLabel("STOP", this);
	lead_status_label->setObjectName("Lead_Label");
	lead_status_label->setStyleSheet("QLabel { color : red; }");
}

void SpO2ParaWidget::initMainLayout()
{
	main_layout = new QVBoxLayout(this);
	main_layout->addWidget(SpO2_label);
	main_layout->addWidget(SpO2_value_label);
	//main_layout->addWidget(PR_label);
	//main_layout->addWidget(PI_label);
	main_layout->addWidget(lead_status_label);
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(10);
}

void SpO2ParaWidget::onSerialPortOpened()
{
	para_status = SpO2ParaStatus::RUN;
}
