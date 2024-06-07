#include "ToolTipWindow.h"
#include <QLabel>
#include <QVBoxLayout>

ToolTipWindow::ToolTipWindow(const QString& text, QWidget* parent)
	:QWidget(parent)
{
    label = new QLabel(text, this);
    label->setStyleSheet(""
        "background-color: rgb(20, 20, 20);"
        "color: #FFFFFF;"
        "border-radius: 7px;" // 设置圆角半径
        "padding: 5px;" // 设置内边距，即包边的宽度
    );
    label->setAlignment(Qt::AlignCenter);
    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

ToolTipWindow::~ToolTipWindow()
{
    delete label;
}

void ToolTipWindow::setToolTip(const QString& s)
{
    label->setText(s);
	label->adjustSize();
	resize(label->size());
}
