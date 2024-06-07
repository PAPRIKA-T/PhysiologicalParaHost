#include "PCTPackDistributor.h"
#include <QDebug>

PCTPackDistributor::PCTPackDistributor(QObject *parent)
	: QObject(parent)
{

}

PCTPackDistributor::~PCTPackDistributor()
{

}

void PCTPackDistributor::DistributePCTData()
{
    StructPCTPackType pack = GetUnPackRslt();
    EnumPCTPackID pack_id = (EnumPCTPackID)pack.packModuleId;
    switch (pack_id) {
       case EnumPCTPackID::MODULE_ECG:
			emit ECG_PCT_DATA(pack);
			break;
       case EnumPCTPackID::MODULE_SPO2:
        emit SPO2_PCT_DATA(pack);
        break;
       case EnumPCTPackID::MODULE_TEMP:
        //qDebug()<<"PCTPackDistributor::TEMP DATA";
        emit TEMP_PCT_DATA(pack);
        break;
       case EnumPCTPackID::MODULE_SYS:
           //qDebug() << "PCTPackDistributor::SYS DATA";
           emit SYS_PCT_DATA(pack);
           break;
        default:
            break;
    }
}

void PCTPackDistributor::UnPackPCTData(const QString& Str)
{
    bool valid = false;
    bool ok = false;
    for (int i = 0; i < Str.length(); i += 3) {
        QString hexPair = Str.mid(i, 2); // 提取两个字符
        int num = hexPair.toInt(&ok, 16); // 转换为整数
        valid = UnPackData(num);
        if (valid) {
            DistributePCTData();
        }
    }
}
