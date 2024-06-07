#include "SerialPortInfoWidget.h"
#include "PspahToolButton.h"
#include <QLabel>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QCheckBox>
#include <QPlainTextEdit>
#include <QThread>

SerialPortInfoWidget::SerialPortInfoWidget(QWidget *parent)
	: QWidget(parent)
{
	setObjectName("SerialPortInfoWidget");
	initMainLayout();
}

SerialPortInfoWidget::~SerialPortInfoWidget()
{
	delete head_tool_layout;
}

QCheckBox* SerialPortInfoWidget::getHexDisplayCheckbox()
{
	return hex_display_checkbox;
}

void SerialPortInfoWidget::onSeiralInfoPush(const QString& s)
{
	//serial_info_browser->moveCursor(QTextCursor::End);
	//serial_info_browser->insertPlainText(s);
	if(serial_info_browser->blockCount()>100)
		serial_info_browser->clear();
	serial_info_browser->appendPlainText(s); 
	//需要解决！！！
	//只有在末尾添加会自动添加bolck，更加高效；
	// 如果在末尾插入，不会自动添加block，随着文本添加，会变得越来越慢
}

void SerialPortInfoWidget::initMainLayout()
{
	main_layout = new QVBoxLayout(this);
	initHeadToolLayout();
	initSeiralInfoWidget();
	main_layout->addLayout(head_tool_layout);
	main_layout->addWidget(serial_info_browser);
	main_layout->setContentsMargins(5, 0, 0, 2);
}

void SerialPortInfoWidget::initHeadToolLayout()
{
	head_tool_layout = new QHBoxLayout();
	serial_port_info_label = new QLabel(tr("SP Info"), this);
	serial_port_info_label->setObjectName("title_label");
	QFont font = serial_port_info_label->font();
	font.setBold(true); // 设置字体加粗
	serial_port_info_label->setFont(font);
	hex_display_label = new QLabel(tr("HEX Display"), this);
	hex_display_checkbox = new QCheckBox(this);
	clear_button = new PspahToolButton(this);
	clear_button->setIcon(QIcon(":/PspahResource/ICON/Rubber.svg"));
	clear_button->setIconSize(QSize(20, 20));
	clear_button->setCustomTooltip("Clear");
	connect(clear_button, &QPushButton::clicked, [=]() {
		serial_info_browser->clear();
		});
	head_tool_layout->addWidget(serial_port_info_label);
	head_tool_layout->addStretch();
	head_tool_layout->addWidget(hex_display_checkbox);
	head_tool_layout->addWidget(hex_display_label);
	head_tool_layout->addSpacing(15);
	head_tool_layout->addWidget(clear_button);
	head_tool_layout->setContentsMargins(0, 0, 0, 0);
	head_tool_layout->setSpacing(0);
}

void SerialPortInfoWidget::initSeiralInfoWidget()
{
	serial_info_browser = new QPlainTextEdit(this);
	serial_info_browser->setReadOnly(true);
	QFont font = QFont();
	font.setPixelSize(15);
	serial_info_browser->setFont(font);
}
