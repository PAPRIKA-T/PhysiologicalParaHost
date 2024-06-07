#pragma once
#include "GenericPCTPackHandler.h"

class SpO2PCTPackHandler  : public GenericPCTPackHandler
{
	Q_OBJECT
public:
	SpO2PCTPackHandler(QObject *parent=nullptr);
	~SpO2PCTPackHandler();
signals:
	void updateValueRED(PCTPackValueID, qreal);
	void updateValueIR(PCTPackValueID, qreal);
public slots:
	virtual void PCTPackHandleTask(StructPCTPackType) override;
};
