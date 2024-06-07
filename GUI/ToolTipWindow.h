#pragma once
#include <QWidget>
class QLabel;
class ToolTipWindow  : public QWidget
{
	Q_OBJECT
public:
	ToolTipWindow(const QString& text, QWidget* parent = nullptr);
	~ToolTipWindow();
	void setToolTip(const QString&);
private:
	QLabel* label{};
};
