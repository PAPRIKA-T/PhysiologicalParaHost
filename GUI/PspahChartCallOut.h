#pragma once
#include <QGraphicsItem>
#include <QFont>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class QChart;

class PspahChartCallOut : public QGraphicsItem
{
public:
    PspahChartCallOut(QChart* parent = nullptr);

    void setText(const QString& text);
    void setAnchor(QPointF point);
    void updateGeometry();

    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event);

private:
    QString text{};
    QRectF textRect{};
    QRectF rect{};
    QPointF anchor{};
    QFont font{};
    QChart* chart{};
};

