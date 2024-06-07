#include "SpO2PCTPackHandler.h"
#include <QDebug>
SpO2PCTPackHandler::SpO2PCTPackHandler(QObject *parent)
	: GenericPCTPackHandler(parent)
{}

SpO2PCTPackHandler::~SpO2PCTPackHandler()
{}

void SpO2PCTPackHandler::PCTPackHandleTask(StructPCTPackType pctdata)
{
	EnumPCTPackID s_id = (EnumPCTPackID)pctdata.packSecondId;
	if (s_id == EnumSPO2SecondID::DAT_SPO2_LEAD)
	{
		//qDebug() << "SPO2 LEAD status:" << (bool)pctdata.arrData[0];
		emit updateValue(PCTPackValueID::LEAD_STATUS, (bool)pctdata.arrData[0]);
	}
	else if (s_id == EnumSPO2SecondID::DAT_SPO2_WAVE)
	{
		qreal red_original_data = PasphGenericOperation::CombineData2816
		(pctdata.arrData[0], pctdata.arrData[1]);
		qreal ir_original_data = PasphGenericOperation::CombineData2816
		(pctdata.arrData[2], pctdata.arrData[3]);
		emit updateValueRED(PCTPackValueID::WAVE_DATA, red_original_data);
		emit updateValueIR(PCTPackValueID::WAVE_DATA, ir_original_data);
	}
	else if (s_id == EnumSPO2SecondID::DAT_SPO2_DATA)
	{
		qreal original_data = PasphGenericOperation::CombineData2816
		(pctdata.arrData[0], pctdata.arrData[1]);
		qreal SpO2Value = original_data / 100;
		if (SpO2Value > 100 || SpO2Value < 0)return;
		emit updateValue(PCTPackValueID::PARA_VALUE, SpO2Value);
	}
	else {
		qDebug() << "SpO2data Rx error";
	}
}
