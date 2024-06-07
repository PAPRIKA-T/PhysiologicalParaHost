#pragma once
#include <QWidget>
#include <Core/PasphMacros.h>
class QPlainTextEdit;
class QHBoxLayout;
class QVBoxLayout;
class PspahGenericButton;
class QCheckBox;
class QLabel;

class SerialPortInfoWidget  : public QWidget
{
	Q_OBJECT
	P_Widget_PaintEventOverride
public:
	SerialPortInfoWidget(QWidget *parent);
	~SerialPortInfoWidget();
	QCheckBox* getHexDisplayCheckbox();
public slots:
	void onSeiralInfoPush(const QString&);
private:
	void initMainLayout();
	void initHeadToolLayout();
	void initSeiralInfoWidget();
	QVBoxLayout* main_layout{};
	QHBoxLayout* head_tool_layout{};
	QLabel* serial_port_info_label{};
	QLabel* hex_display_label{};
	QCheckBox* hex_display_checkbox{};
	PspahGenericButton* clear_button{};

	QPlainTextEdit* serial_info_browser{};
};
