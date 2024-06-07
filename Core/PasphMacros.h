#pragma once
#include <QStyleOption>
#include <QStyleOptionButton>
#include <QPainter>
#include <QMouseEvent>

#define ECG_SERIES_COLOR QColor("#1dc320")
#define SPO2_SERIES_COLOR_RED QColor("#FF0000")
#define SPO2_SERIES_COLOR_IR QColor("#e132e7")
#define P_Widget_PaintEventOverride \
protected: \
    virtual void paintEvent(QPaintEvent *event) override{\
        Q_UNUSED(event);\
        QStyleOption styleOpt;\
        styleOpt.initFrom(this);\
        QPainter painter(this);\
        style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);\
    };\

#define P_PushButton_PaintEventOverride \
protected: \
    virtual void paintEvent(QPaintEvent* event) override {\
        Q_UNUSED(event);\
        QStyleOptionButton styleOpt;\
        styleOpt.initFrom(this);\
        QPainter painter(this);\
        style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);\
        QPushButton::paintEvent(event);\
    }; \