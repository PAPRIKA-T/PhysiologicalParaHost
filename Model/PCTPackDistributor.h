#pragma once
#include <QObject>
#include "Core/PCTPackUnpack.h"
class PCTPackDistributor  : public QObject
{
	Q_OBJECT
public:
	PCTPackDistributor(QObject *parent = nullptr);
	~PCTPackDistributor();

signals:
	void TEMP_PCT_DATA(StructPCTPackType);
	void ECG_PCT_DATA(StructPCTPackType);
	void SPO2_PCT_DATA(StructPCTPackType);
	void SYS_PCT_DATA(StructPCTPackType);
public slots:
	void UnPackPCTData(const QString&);
private:
	void DistributePCTData();
};
