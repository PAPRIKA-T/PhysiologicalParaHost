#pragma once
#include <QtCharts/QChartView>
class QValueAxis;
class QChart;
class QScatterSeries;
class QLineSeries;
class PspahChartCallOut;
class QTimer;
class DynamicTaskModel;
class QThread;

class PspahChartView  : public QChartView
{
	Q_OBJECT
public:
    explicit PspahChartView(QWidget* parent = nullptr);
	~PspahChartView();
    void setSeriesColor(const QColor& color);
    //void setChartXRange(qreal min, qreal max);
    void setChartYRange(qreal min, qreal max);
    DynamicTaskModel* getDynamicTaskModel();
    void resetDataBackup();
    void saveDataBackup();
protected:
    //void keyPressEvent(QKeyEvent* event);
    //void mousePressEvent(QMouseEvent* event);
    //void mouseMoveEvent(QMouseEvent* event);
    //void mouseReleaseEvent(QMouseEvent* event);
    //void wheelEvent(QWheelEvent* event);
signals:
    void setTimerInterval(int);
    void timerStart();
    void timerStop();
private slots:
    void tipSlot(const QPointF& position, bool isHovering);
    void updateLineSeriesData(const QVector<QPointF>&);
    void updateScatterSeriesData(const QPointF&);
    void onUpdataMaxX(int);
    void onUpdateYRange(qreal, qreal);
private:
    void initChart();
    void initSlot();
    void initDynamicTaskModel();
    void resetChart();
    DynamicTaskModel* dynamic_task_model{};
    QThread* thread{};
    QChart* chart{};
    QValueAxis* axisX{};
    QValueAxis* axisY{};
    QScatterSeries* scatter_series{};
    QLineSeries* line_series{};
    PspahChartCallOut* tip{};
    bool isClicking;
    int xOld;
    int yOld;
};
