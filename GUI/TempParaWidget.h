#pragma once
#include <QWidget>
#include "Core/PCTPackUnpack.h"
#include "Model/TempPCTPackHandler.h"
class QLabel;
class QVBoxLayout;
class QThread;
class PCTPackDistributor;

class TempParaWidget  : public QWidget
{
	Q_OBJECT
	enum class TempLeadStatus
	{
		LeadOff,
		LeadOn,
		NONE,
	};
	enum class TempParaStatus
	{
		RUN,
		STOP,
	};
public:
	TempParaWidget(QWidget *parent=nullptr);
	~TempParaWidget();
	void connectPCTDistributorSignals(PCTPackDistributor* d);
	void resetTempLabel();
	GenericPCTPackHandler* getPCTPackHandler();
public slots:
	void onSerialPortOpened();
private:
	void updateTempValue(qreal value);
	void updateLeadStatus(TempLeadStatus);
	void initMainLayout();
	void initHandler();
	void onUpdateValue(TempPCTPackHandler::PCTPackValueID, qreal);
	QVBoxLayout* main_layout{};
	QLabel* Temp_label{};
	QLabel* Temp_value_label{};
	QLabel* lead_status_label{};
	TempLeadStatus lead_status{ TempLeadStatus::NONE };
	TempParaStatus para_status{ TempParaStatus::STOP };
	qreal TempValue{0};
	TempPCTPackHandler* handler{};
	QThread* handler_thread{};
};
