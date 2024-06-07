#include "TempPCTPackHandler.h"
#include <QDebug>

TempPCTPackHandler::TempPCTPackHandler(QObject *parent)
	: GenericPCTPackHandler(parent)
{}

TempPCTPackHandler::~TempPCTPackHandler()
{}

void TempPCTPackHandler::PCTPackHandleTask(StructPCTPackType pctdata)
{
	EnumPCTPackID s_id = (EnumPCTPackID)pctdata.packSecondId;
	if (s_id == EnumTempSecondID::DAT_TEMP_LEAD)
	{
		emit updateValue(PCTPackValueID::LEAD_STATUS,(bool)pctdata.arrData[0]);
	}
	else if (s_id == EnumTempSecondID::DAT_TEMP_DATA)
	{
		qreal original_data = PasphGenericOperation::CombineData2816
		(pctdata.arrData[0], pctdata.arrData[1]);
		qreal TempValue = original_data / 10;
		if (TempValue > 80 || TempValue < 0)return;
		//qDebug() << "Temp: " << TempValue;
		emit updateValue(PCTPackValueID::PARA_VALUE,TempValue);
	}
}
