#pragma once
#include <QWidget>
#include <Core/PasphMacros.h>
class PspahChartView;
class QHBoxLayout;
class QVBoxLayout;
class PspahGenericButton;
class PspahGenericChartWidget  : public QWidget
{
	Q_OBJECT
	P_Widget_PaintEventOverride
public:
	PspahGenericChartWidget(QWidget *parent=nullptr);
	~PspahGenericChartWidget();
	PspahChartView* getPspahChartView();
	void setSeriesColor(const QColor& color);
	//void setChartXRange(qreal min, qreal max);
	void setChartYRange(qreal min, qreal max);
	void setTimerInterval(int);
	void timerStart();
	void timerStop();
signals:

private slots:
	void onTimerBtnClicked();
	void onResetBtnClicked();
	void onSaveBtnClicked();
private:
	void initMainLayout();
	void initSlot();
	QVBoxLayout* main_layout{};
	PspahChartView* chart_view{};
	QVBoxLayout* keep_right_layout{};
	QHBoxLayout* tool_layout{};
	PspahGenericButton* timmer_btn{};
	PspahGenericButton* reset_data_btn{};
	PspahGenericButton* save_data_btn{};
	bool is_running{ true };
};
