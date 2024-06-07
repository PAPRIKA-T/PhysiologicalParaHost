#pragma once
#include <QWidget>
#include "Core/PCTPackUnpack.h"
#include "Model/EcgPCTPackHandler.h"
class QLabel;
class QVBoxLayout;
class PCTPackDistributor;
class QThread;
class ECGParaWidget  : public QWidget
{
	Q_OBJECT
public:
	enum class ECGLeadStatus
	{
		LeadOff,
		LeadOn,
		NONE,
	};
	enum class ECGParaStatus
	{
		RUN,
		STOP,
	};
	ECGParaWidget(QWidget *parent);
	~ECGParaWidget();
	void connectPCTDistributorSignals(PCTPackDistributor* d);
	void resetECGLabel();
	EcgPCTPackHandler* getPCTPackHandler();
public slots:
	void onSerialPortOpened();
private:
	void updateECGValue(int value);
	void updateLeadStatus(ECGLeadStatus);
	void initMainLayout();
	void initHandler();
	void onUpdateValue(EcgPCTPackHandler::PCTPackValueID, qreal);
	QVBoxLayout* main_layout{};
	QLabel* ECG_label{};
	QLabel* ECG_value_label{};
	QLabel* lead_status_label{};
	ECGLeadStatus lead_status{ ECGLeadStatus::NONE };
	ECGParaStatus para_status{ ECGParaStatus::STOP };
	qreal ECG_Value{0};
	QThread* handler_thread{};
	EcgPCTPackHandler* handler{};
};
