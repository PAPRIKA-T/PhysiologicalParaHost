#include "PspahWaveSetWidget.h"
#include "PspahGenericChartWidget.h"
#include "PspahSetWidget.h"
#include "GUI/ECGParaWidget.h"
#include "GUI/SpO2ParaWidget.h"
#include "GUI/TempParaWidget.h"
#include "PspahChartView.h"
#include "Model/DynamicTaskModel.h"
#include <QVBoxLayout>

PspahWaveSetWidget::PspahWaveSetWidget(QWidget*parent)
	: QWidget(parent)
{
	setObjectName("PspahWaveSetWidget");
	initLayout();
}

PspahWaveSetWidget::~PspahWaveSetWidget()
{
	delete SpO2_layout;
	delete main_layout;
}

void PspahWaveSetWidget::connectPspahSetWidgetSignals(PspahSetWidget* p)
{
	connect(p->getECGParaWidget()->getPCTPackHandler(), &EcgPCTPackHandler::updateValue,
		pasph_ECG_chart_widget->getPspahChartView()->getDynamicTaskModel(), &DynamicTaskModel::onUpdatePCTData);

	connect(p->getSpO2ParaWidget()->getPCTPackHandler(), &SpO2PCTPackHandler::updateValue,
		pasph_SpO2RED_chart_widget->getPspahChartView()->getDynamicTaskModel(), &DynamicTaskModel::onUpdatePCTData);
	connect(p->getSpO2ParaWidget()->getPCTPackHandler(), &SpO2PCTPackHandler::updateValueRED,
		pasph_SpO2RED_chart_widget->getPspahChartView()->getDynamicTaskModel(), &DynamicTaskModel::onUpdatePCTData);

	connect(p->getSpO2ParaWidget()->getPCTPackHandler(), &SpO2PCTPackHandler::updateValue,
		pasph_SpO2IR_chart_widget->getPspahChartView()->getDynamicTaskModel(), &DynamicTaskModel::onUpdatePCTData);
	connect(p->getSpO2ParaWidget()->getPCTPackHandler(), &SpO2PCTPackHandler::updateValueIR,
		pasph_SpO2IR_chart_widget->getPspahChartView()->getDynamicTaskModel(), &DynamicTaskModel::onUpdatePCTData);
}

void PspahWaveSetWidget::initLayout()
{
	main_layout = new QVBoxLayout(this);
	pasph_ECG_chart_widget = new PspahGenericChartWidget(this);
	pasph_ECG_chart_widget->setObjectName("ECGChartWidget");
	pasph_ECG_chart_widget->setSeriesColor(ECG_SERIES_COLOR);
	pasph_ECG_chart_widget->getPspahChartView()->getDynamicTaskModel()->setObjectName("ECGChartWidget");
	pasph_ECG_chart_widget->setTimerInterval(20);

	SpO2_layout = new QHBoxLayout();
	pasph_SpO2RED_chart_widget = new PspahGenericChartWidget(this);
	pasph_SpO2RED_chart_widget->setObjectName("SpO2ChartWidgetRED");
	pasph_SpO2RED_chart_widget->getPspahChartView()->getDynamicTaskModel()->setObjectName("SpO2ChartWidgetRED");
	pasph_SpO2RED_chart_widget->setSeriesColor(SPO2_SERIES_COLOR_RED);
	pasph_SpO2RED_chart_widget->setTimerInterval(50);

	pasph_SpO2IR_chart_widget = new PspahGenericChartWidget(this);
	pasph_SpO2IR_chart_widget->setObjectName("SpO2ChartWidgetIR");
	pasph_SpO2IR_chart_widget->setSeriesColor(SPO2_SERIES_COLOR_IR);
	pasph_SpO2IR_chart_widget->getPspahChartView()->getDynamicTaskModel()->setObjectName("SpO2ChartWidgetIR");
	pasph_SpO2IR_chart_widget->setTimerInterval(50);
	SpO2_layout->addWidget(pasph_SpO2RED_chart_widget);
	SpO2_layout->addWidget(pasph_SpO2IR_chart_widget);

	main_layout->addWidget(pasph_ECG_chart_widget);
	main_layout->addLayout(SpO2_layout);
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(0);
}
