#include "PspahGenericChartWidget.h"
#include "PspahChartView.h"
#include "PspahToolButton.h"
#include <QVBoxLayout>
#include <QTimer>
#include <QThread>
PspahGenericChartWidget::PspahGenericChartWidget(QWidget *parent)
	: QWidget(parent)
{
	setObjectName("PspahGenericChartWidget");
    chart_view = new PspahChartView();
    initMainLayout();
    initSlot();
}

PspahGenericChartWidget::~PspahGenericChartWidget()
{
    delete main_layout;
    delete tool_layout;
    delete keep_right_layout;
    chart_view->deleteLater();
}

PspahChartView* PspahGenericChartWidget::getPspahChartView()
{
    return chart_view;
}

void PspahGenericChartWidget::setSeriesColor(const QColor& color)
{
    chart_view->setSeriesColor(color);
}

//void PspahGenericChartWidget::setChartXRange(qreal min, qreal max)
//{
//    chart_view->setChartXRange(min, max);
//}

void PspahGenericChartWidget::setChartYRange(qreal min, qreal max)
{
    chart_view->setChartYRange(min, max);
}

void PspahGenericChartWidget::setTimerInterval(int i)
{
    emit chart_view->setTimerInterval(i);
}

void PspahGenericChartWidget::timerStart()
{
    if (is_running) return;
	emit chart_view->timerStart();
	timmer_btn->setIcon(QIcon(":/PspahResource/ICON/GreenPoint.png"));
	is_running = !is_running;
}

void PspahGenericChartWidget::timerStop()
{
    if (!is_running) return;
    emit chart_view->timerStop();
    timmer_btn->setIcon(QIcon(":/PspahResource/ICON/RedPoint.png"));
    is_running = !is_running;
}

void PspahGenericChartWidget::onResetBtnClicked()
{
    chart_view->resetDataBackup();
}

void PspahGenericChartWidget::onSaveBtnClicked()
{
    chart_view->saveDataBackup();
}

void PspahGenericChartWidget::initMainLayout()
{
    main_layout = new QVBoxLayout(this);
    main_layout->addWidget(chart_view);
    main_layout->setContentsMargins(0, 0, 0, 0);

    keep_right_layout = new QVBoxLayout(chart_view);
    tool_layout = new QHBoxLayout();
    keep_right_layout->addLayout(tool_layout);
    keep_right_layout->addStretch();

    timmer_btn = new PspahToolButton(this);
    timmer_btn->setCustomTooltip("Stop");
    //timmer_btn->setVisible(false);
    timmer_btn->setIcon(QIcon(":/PspahResource/ICON/GreenPoint.png"));

    save_data_btn = new PspahToolButton(this);
    save_data_btn->setCustomTooltip("Save");
    save_data_btn->setIcon(QIcon(":/PspahResource/ICON/Save.svg"));
    save_data_btn->setIconSize(QSize(20, 20));

    reset_data_btn = new PspahToolButton(this);
    reset_data_btn->setCustomTooltip("Reset");
    reset_data_btn->setIcon(QIcon(":/PspahResource/ICON/Reset.svg"));
    tool_layout->addStretch();
    tool_layout->addWidget(reset_data_btn);
    tool_layout->addWidget(save_data_btn);
    tool_layout->addWidget(timmer_btn);
    tool_layout->setContentsMargins(0, 0, 0, 0);
    tool_layout->setSpacing(0);
}

void PspahGenericChartWidget::initSlot()
{
    connect(timmer_btn, &PspahGenericButton::clicked, this, &PspahGenericChartWidget::onTimerBtnClicked);
    connect(reset_data_btn, &PspahGenericButton::clicked, this, &PspahGenericChartWidget::onResetBtnClicked);
    connect(save_data_btn, &PspahGenericButton::clicked, this, &PspahGenericChartWidget::onSaveBtnClicked);
}

void PspahGenericChartWidget::onTimerBtnClicked()
{
    if (is_running) {
        timerStop();
        timmer_btn->setCustomTooltip("Start");
	}
    else {
        timerStart();
        timmer_btn->setCustomTooltip("Stop");
	}
}
