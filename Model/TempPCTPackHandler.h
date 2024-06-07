#pragma once
#include "GenericPCTPackHandler.h"
class TempPCTPackHandler  : public GenericPCTPackHandler
{
	Q_OBJECT
public:
	TempPCTPackHandler(QObject *parent = nullptr);
	~TempPCTPackHandler();
public slots:
	virtual void PCTPackHandleTask(StructPCTPackType) override;
};
