#pragma once
#include <QWidget>
#include "Core/PCTPackUnpack.h"
#include "Model/SpO2PCTPackHandler.h"
class QLabel;
class QVBoxLayout;
class QThread;
class PCTPackDistributor;

class SpO2ParaWidget  : public QWidget
{
	Q_OBJECT
public:
	enum class SpO2LeadStatus
	{
		LeadOff,
		LeadOn,
		NONE,
	};
	enum class SpO2ParaStatus
	{
		RUN,
		STOP,
	};
	SpO2ParaWidget(QWidget *parent);
	~SpO2ParaWidget();
	void resetSpO2Label();
	void connectPCTDistributorSignals(PCTPackDistributor* d);
	SpO2PCTPackHandler* getPCTPackHandler();
public slots:
	void onSerialPortOpened();
private:
	void initSelf();
	void initMainLayout();
	void updateSpO2Value(qreal value);
	void updatePRValue(int value);
	void updatePIValue(qreal value);
	void updateLeadStatus(SpO2LeadStatus);
	void initHandler();
	void onUpdateValue(SpO2PCTPackHandler::PCTPackValueID, qreal);
	QVBoxLayout* main_layout{};
	QLabel* SpO2_label{};
	QLabel* SpO2_value_label{};
	//QLabel* PR_label{};
	//QLabel* PI_label{};
	QLabel* lead_status_label{};
	SpO2LeadStatus lead_status{ SpO2LeadStatus::NONE };
	SpO2ParaStatus para_status{ SpO2ParaStatus::STOP };
	qreal SpO2Value{};
	QThread* handler_thread{};
	SpO2PCTPackHandler* handler{};
};
