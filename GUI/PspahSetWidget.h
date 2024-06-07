#pragma once
#include <QWidget>
#include <Core/PasphMacros.h>
#include "Core/PCTPackUnpack.h"
class QVBoxLayout;
class ECGParaWidget;
class SpO2ParaWidget;
class TempParaWidget;
class QLabel;
class PCTPackDistributor;
class SerialPortSettingsWidget;

class PspahSetWidget : public QWidget
{
	Q_OBJECT
	P_Widget_PaintEventOverride
public:
	PspahSetWidget(QWidget* parent);
	~PspahSetWidget();
	void connectPCTDistributorSignals(PCTPackDistributor*);
	void connectSerialPortSignals(SerialPortSettingsWidget*);
	ECGParaWidget* getECGParaWidget();
	SpO2ParaWidget* getSpO2ParaWidget();
	TempParaWidget* getTempParaWidget();
public slots:
	
	void onSerialPortClosed();
	void onSYS_PCT_DATA(StructPCTPackType);
private:
	void startParaSetLabel();
	void resetParaSetLabel();
	void initMainLayout();
	void initThreadPool();
	QVBoxLayout* main_layout{};
	QLabel* pasph_label{};
	ECGParaWidget* ecg_para_widget{};
	SpO2ParaWidget* spo2_para_widget{};
	TempParaWidget* temp_para_widget{};
};
