#pragma once
#include <QObject>
#include "Core/PCTPackUnpack.h"
#include "Core/PasphGenericOperation.h"
class GenericPCTPackHandler  : public QObject
{
	Q_OBJECT
public:
	enum class PCTPackValueID {
		LEAD_STATUS,
		WAVE_DATA,
		PARA_VALUE,
	};
signals:
	void updateValue(PCTPackValueID, qreal);
protected:
	GenericPCTPackHandler(QObject *parent);
	~GenericPCTPackHandler();
	virtual void PCTPackHandleTask(StructPCTPackType) = 0;
};
