#pragma once
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QPainter>

class CustomTabStyle  : public QProxyStyle
{
	Q_OBJECT
public:
    //将原来的tab转置，重新绘制，实现到左右旁边，还可以在tabPosition中再次设置
    QSize sizeFromContents(ContentsType type, const QStyleOption* option,
        const QSize& size, const QWidget* widget) const;

    void drawControl(ControlElement element, const QStyleOption* option,
        QPainter* painter, const QWidget* widget) const;

};
