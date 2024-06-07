#pragma once

#include "GenericPCTPackHandler.h"

class EcgPCTPackHandler  : public GenericPCTPackHandler
{
	Q_OBJECT
public:
	EcgPCTPackHandler(QObject *parent=nullptr);
	~EcgPCTPackHandler();
public slots:
	virtual void PCTPackHandleTask(StructPCTPackType) override;
};
