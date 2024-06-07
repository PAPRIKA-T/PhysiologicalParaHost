#include "PspahToolButton.h"
#include <QStyleOptionButton>
#include <QPainter>

PspahToolButton::PspahToolButton(QWidget* parent)
    : PspahGenericButton(parent)
{
    setFixedSize(30, 30);
}

PspahToolButton::PspahToolButton(const QString& text, QWidget* parent)
    :PspahGenericButton(text, parent)
{
    setFixedSize(30, 30);
}

PspahToolButton::~PspahToolButton()
{

}

void PspahToolButton::paintEvent(QPaintEvent* event)
{
    QStyleOptionButton  styleOpt;
    styleOpt.initFrom(this);
    QPainter painter(this);
    style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
    QPushButton::paintEvent(event);
}
