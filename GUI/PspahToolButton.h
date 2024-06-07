#pragma once
#include "PspahGenericButton.h"

class PspahToolButton : public PspahGenericButton
{
	Q_OBJECT
public:
	PspahToolButton(QWidget* parent = nullptr);
	PspahToolButton(const QString& text, QWidget* parent = nullptr); //构造函数重载
	~PspahToolButton();
	virtual void paintEvent(QPaintEvent* event) override;
};
