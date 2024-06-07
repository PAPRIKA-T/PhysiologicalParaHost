#include "PspahChartView.h"
#include "PspahChartCallOut.h"
#include "Model/DynamicTaskModel.h"
#include <QGraphicsLayout>
#include <QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QChart>
#include <QTimer>
#include <QThread>

PspahChartView::PspahChartView(QWidget* parent) :
    QChartView(parent),
    isClicking(false),
    xOld(0), yOld(0)
{
    setObjectName("PspahChartView");
    setRenderHint(QPainter::Antialiasing);
    initChart();
    setRubberBand(QChartView::NoRubberBand);
    initDynamicTaskModel();
    initSlot();
}

PspahChartView::~PspahChartView()
{
    if (tip != nullptr) {
        delete tip;
        tip = nullptr;
    };
    dynamic_task_model->deleteLater();
    thread->deleteLater();
    delete axisX;
    delete axisY;
    delete scatter_series;
    delete line_series;
    delete chart;
}

void PspahChartView::initChart()
{
    chart = new QChart;
    setChart(chart);

    scatter_series = new QScatterSeries;
    scatter_series->setMarkerShape(QScatterSeries::MarkerShapeRotatedRectangle);
    scatter_series->setMarkerSize(16);
    line_series = new QLineSeries;
    line_series->setMarkerSize(1);
    line_series->setPointsVisible(false);
    line_series->setUseOpenGL(true);
    line_series->setVisible(true);
    chart->addSeries(scatter_series);
    chart->addSeries(line_series);

    axisX = new QValueAxis;
    axisX->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    axisX->setLabelFormat("%d");
    axisX->setRange(AXIS_MIN_X, DEFAULT_DATA_SIZE);
    //axisX->setTickCount(11);
    axisX->setVisible(false);
    //axisX->setMinorTickCount(4);
    //axisX->setGridLineVisible(true);

    axisY = new QValueAxis;
    axisY->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
    axisY->setLabelFormat("%d");
    axisY->setRange(AXIS_MIN_Y, AXIS_MAX_Y);
    //axisY->setTickCount(AXIS_MAX_Y+1);
    //axisY->setMinorTickCount(4);
    //axisY->setTitleText("Amplitude/mV");
    //axisY->setGridLineVisible(true);

    chart->addAxis(axisX, Qt::AlignBottom);
    line_series->attachAxis(axisX);
    scatter_series->attachAxis(axisX);
    chart->addAxis(axisY, Qt::AlignLeft);
    line_series->attachAxis(axisY);
    scatter_series->attachAxis(axisY);
    /* hide legend */
    chart->legend()->hide();
    chart->layout()->setContentsMargins(2, 2, 2, 2);//设置外边界全部为0
    chart->setMargins(QMargins(2, 2, 2, 2));//设置内边界全部为0
}

void PspahChartView::initSlot()
{
    //connect(scatter_series, SIGNAL(hovered(const QPointF&, bool)),
    //    this, SLOT(tipSlot(const QPointF&, bool)));

    connect(this, &PspahChartView::setTimerInterval,
        dynamic_task_model, &DynamicTaskModel::onSetTimerInterval);
    connect(this, &PspahChartView::timerStart,
        dynamic_task_model, &DynamicTaskModel::onTimerStrat);
    connect(this, &PspahChartView::timerStop,
        dynamic_task_model, &DynamicTaskModel::onTimerStop);

    connect(dynamic_task_model, static_cast<void (DynamicTaskModel::*)(const QVector<QPointF>&)>
        (&DynamicTaskModel::transmitLineSeriesData),
        this, static_cast<void (PspahChartView::*)(const QVector<QPointF>&)>
        (&PspahChartView::updateLineSeriesData));

    connect(dynamic_task_model, static_cast<void (DynamicTaskModel::*)(const QPointF&)>
        (&DynamicTaskModel::transmitScatterSeriesData),
        this, static_cast<void (PspahChartView::*)(const QPointF&)>
        (&PspahChartView::updateScatterSeriesData));

    connect(dynamic_task_model, &DynamicTaskModel::updateMaxX,
        this, &PspahChartView::onUpdataMaxX);
    connect(dynamic_task_model, &DynamicTaskModel::updateYRange,
        this, &PspahChartView::onUpdateYRange);
}

void PspahChartView::initDynamicTaskModel()
{
    dynamic_task_model = new DynamicTaskModel();
    thread = new QThread();
    dynamic_task_model->moveToThread(thread);
    thread->start();
    dynamic_task_model->dynamicTaskBegin();
}

void PspahChartView::resetChart()
{ 
    chart->zoomReset();
    chart->scroll(0, 0);
}


void PspahChartView::updateLineSeriesData(const QVector<QPointF>& data)
{
    line_series->replace(data);
}

void PspahChartView::updateScatterSeriesData(const QPointF& data)
{
    scatter_series->clear();
    scatter_series->append(data);
}

void PspahChartView::onUpdataMaxX(int m)
{
    axisX->setRange(AXIS_MIN_X, m);
}

void PspahChartView::onUpdateYRange(qreal min, qreal max)
{
    axisY->setRange(min, max);
}

void PspahChartView::setSeriesColor(const QColor& color)
{
    line_series->setColor(color);
    scatter_series->setColor(color);
}

//void PspahChartView::setChartXRange(qreal min, qreal max)
//{
//    axisX->setRange(min, max);
//}

void PspahChartView::setChartYRange(qreal min, qreal max)
{
    axisY->setRange(min, max);
}

DynamicTaskModel* PspahChartView::getDynamicTaskModel()
{
    return dynamic_task_model;
}

void PspahChartView::resetDataBackup()
{
    dynamic_task_model->onResetDataBackup();
}

void PspahChartView::saveDataBackup()
{
    dynamic_task_model->onSaveDataBackup();
}

void PspahChartView::tipSlot(const QPointF& position, bool isHovering)
{
    if (tip == nullptr)
        tip = new PspahChartCallOut(chart);
    qDebug() << isHovering;
    if (isHovering) {
        tip->setText(QString("X: %1 \nY: %2 ").arg(position.x()).arg(position.y()));
        tip->setAnchor(position);
        tip->setZValue(11);
        tip->updateGeometry();
        tip->show();
    }
    else {
        tip->hide();
    }
}


//void PspahChartView::mousePressEvent(QMouseEvent* event)
//{
//    if (event->button() & Qt::LeftButton) {
//        isClicking = true;
//    }
//    else if (event->button() & Qt::RightButton) {
//        chart->zoomReset();
//    }
//
//    QChartView::mousePressEvent(event);
//}

//void PspahChartView::mouseMoveEvent(QMouseEvent* event)
//{
//    int x, y;
//
//    if (isClicking) {
//        if (xOld == 0 && yOld == 0) {
//
//        }
//        else {
//            x = event->pos().x() - xOld;
//            y = event->pos().y() - yOld;
//            qDebug()<< "x:" << x <<"y:" << y;
//            chart->scroll(-x, y);
//        }
//
//        xOld = event->pos().x();
//        yOld = event->pos().y();
//
//        return;
//    }
//
//    QChartView::mouseMoveEvent(event);
//}

//void PspahChartView::mouseReleaseEvent(QMouseEvent* event)
//{
//    if (isClicking) {
//        xOld = yOld = 0;
//        isClicking = false;
//    }
//
//    /* Disable original right click event */
//    if (!(event->button() & Qt::RightButton)) {
//        QChartView::mouseReleaseEvent(event);
//    }
//}

//void PspahChartView::keyPressEvent(QKeyEvent* event)
//{
//    switch (event->key()) {
//    case Qt::Key_Left:
//        chart->scroll(-10, 0);
//        break;
//    case Qt::Key_Right:
//        chart->scroll(10, 0);
//        break;
//    case Qt::Key_Up:
//        chart->scroll(0, 10);
//        break;
//    case Qt::Key_Down:
//        chart->scroll(0, -10);
//        break;
//    default:
//        keyPressEvent(event);
//        break;
//    }
//}

//void PspahChartView::wheelEvent(QWheelEvent* event)
//{
//    if (event->angleDelta().y() > 0) {
//        chart->zoom(1.1);
//    }
//    else {
//        chart->zoom(10.0 / 11);
//    }
//}