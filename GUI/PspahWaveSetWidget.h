#pragma once
#include <QWidget>
#include <Core/PasphMacros.h>
class PspahGenericChartWidget;
class QHBoxLayout;
class QVBoxLayout;
class PspahSetWidget;

class PspahWaveSetWidget  : public QWidget
{
	Q_OBJECT
	P_Widget_PaintEventOverride
public:
	PspahWaveSetWidget(QWidget*parent);
	~PspahWaveSetWidget();
	void connectPspahSetWidgetSignals(PspahSetWidget*);
private:
	void initLayout();
	QVBoxLayout* main_layout{};
	QHBoxLayout* SpO2_layout{};
	PspahGenericChartWidget* pasph_ECG_chart_widget{};
	PspahGenericChartWidget* pasph_SpO2RED_chart_widget{};
	PspahGenericChartWidget* pasph_SpO2IR_chart_widget{};
};
