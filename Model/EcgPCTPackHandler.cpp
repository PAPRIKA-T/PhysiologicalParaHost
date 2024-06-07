#include "EcgPCTPackHandler.h"
#include <QDebug>
EcgPCTPackHandler::EcgPCTPackHandler(QObject *parent)
	: GenericPCTPackHandler(parent)
{}

EcgPCTPackHandler::~EcgPCTPackHandler()
{}

void EcgPCTPackHandler::PCTPackHandleTask(StructPCTPackType pctdata)
{
	EnumPCTPackID s_id = (EnumPCTPackID)pctdata.packSecondId;
	if (s_id == EnumECGSecondID::DAT_ECG_WAVE)
	{
		qreal ECG_WAVE = PasphGenericOperation::CombineData2816
		(pctdata.arrData[0], pctdata.arrData[1]);
		//qDebug() << "ECG WAVE:" << ECG_WAVE-2000;
		emit updateValue(PCTPackValueID::WAVE_DATA, ECG_WAVE-2000);
	}
	else if (s_id == EnumECGSecondID::DAT_ECG_LEAD)
	{
		//qDebug() << "ECG LEAD:" << (bool)!pctdata.arrData[0];
		emit updateValue(PCTPackValueID::LEAD_STATUS, (bool)!pctdata.arrData[0]);
	}
	else if (s_id == EnumECGSecondID::DAT_ECG_HR)
	{
		qreal HRValue = PasphGenericOperation::CombineData2816
		(pctdata.arrData[0], pctdata.arrData[1]);
		qDebug() << "ECG HR:" << HRValue;
		emit updateValue(PCTPackValueID::PARA_VALUE, HRValue);
	}
}
