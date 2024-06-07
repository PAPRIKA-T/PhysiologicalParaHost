#pragma once
#include <QPushButton>
#include <QEnterEvent>
class ToolTipWindow;

class PspahGenericButton : public QPushButton
{
protected :
	PspahGenericButton(QWidget* parent = nullptr);
	PspahGenericButton(const QString& text, QWidget* parent = nullptr); //构造函数重载
	~PspahGenericButton();
	virtual void enterEvent(QEnterEvent* event); //鼠标进入事件
	virtual void leaveEvent(QEvent* event) override; //鼠标离开事件

public:
	void setCustomTooltip(const QString& tooltip);//设置提示文字的函数

private:
	ToolTipWindow* tooltip_window = nullptr;
	QString tooltip_text;
	bool is_set_custom_tooltip = false;
};
