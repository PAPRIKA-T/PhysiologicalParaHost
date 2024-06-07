﻿#include "PCTPackUnpack.h"
#include <QDebug>
//以下四个参数在打包和解包的时候使用
static StructPCTPackType s_ptPack;   //数据包，1字节模块ID，1字节数据头，1字节二级ID，6字节数据，1字节校验和
static u8       s_iPackLen;       //数据包长度，用来判断数据长度是否为10，不为10为错误包
static u8       s_iGotPackId;     //获取到ID的标志
static u8       s_iRestByteNum;   //剩余字节数

/*********************************************************************************************************
*                                              内部函数声明
*********************************************************************************************************/
static  void  PackWithCheckSum(u8* pPack);    //带校验和的数据打包
static  u8    UnpackWithCheckSum(u8* pPack);  //带校验和的数据解包

/*********************************************************************************************************
*                                              内部函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称：PackWithCheckSum
* 函数功能：带校验和的数据打包
* 输入参数：待打包的数据pPack的首地址
* 输出参数：打包好的数据pPack的首地址
* 返 回 值：void
* 创建日期：2018年01月01日
* 注    意：如数据头的BIT0为二级ID的BIT7，数据头的BIT1为数据1的BIT7，数据头的BIT2为数据2的BIT7，数据头的
*           BIT6为数据6的BIT7
*********************************************************************************************************/
static void PackWithCheckSum(u8* pPack)
{
    u8  i;
    u8  dataHead;   //数据头，在数据包的第2个位置，即ModuleID之后
    u8  checkSum;   //校验和，在数据包的最后一个位置

    checkSum = *(pPack);  //取出ModuleID，加到校验和
    dataHead = 0;         //数据头清零

    for (i = 8; i > 1; i--)
    {
        //数据头左移，后面数据的最高位位于dataHead的靠左，如数据6的最高位位于dataHead的BIT6
        dataHead <<= 1;

        //取出原始数据的最高位，与dataHead相或
        dataHead |= (*(pPack + i) & 0x80) >> 7;

        //对数据进行最高位置1操作，并将数据右移一位（数据头插入原因）
        *(pPack + i) = *(pPack + i) | 0x80;

        //数据加到校验和
        checkSum += *(pPack + i);
    }

    //数据头在数据包的第二个位置，仅次于包头，数据头的最高位也要置为1
    *(pPack + 1) = dataHead | 0x80;

    //将数据头加到校验和
    checkSum += *(pPack + 1);

    //校验和的最高位也要置为1
    *(pPack + 9) = checkSum | 0x80;
}

/*********************************************************************************************************
* 函数名称：UnpackWithCheckSum
* 函数功能：带校验和的数据解包
* 输入参数：待解包的数据pPack的首地址，打包后的数据长度
* 输出参数：解包好的数据pPack的首地址
* 返 回 值：0-解包不成功，1-解包成功
* 创建日期：2018年01月01日
* 注    意：
*********************************************************************************************************/
static u8  UnpackWithCheckSum(u8* pPack)
{
    u8  i;
    u8  dataHead;   //数据头，在数据包的第2个位置，即ModuleID之后            
    u8  checkSum;   //校验和，在数据包的最后一个位置

    checkSum = *(pPack);       //取出模块ID，加到校验和

    dataHead = *(pPack + 1);    //取出数据包的数据头，赋给dataHead
    checkSum += dataHead;       //将数据头加到校验和

    for (i = 2; i < 9; i++)
    {
        checkSum += *(pPack + i); //将数据依次加到校验和

        //还原二级ID和6位数据
        *(pPack + i) = (*(pPack + i) & 0x7f) | ((dataHead & 0x1) << 7);

        dataHead >>= 1;           //数据头右移一位
    }

    //判断模块ID、数据头、二级ID和数据求和的结果（低七位）是否与校验和的低七位相等，如果不等返回0
    if ((checkSum & 0x7f) != ((*(pPack + 9)) & 0x7f))
    {
        return 0;
    }

    return 1;
}

/*********************************************************************************************************
*                                              API函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称：InitPackUnpack
* 函数功能：初始化PackUnpack模块，其余参数均默认为0
* 输入参数：void
* 输出参数：void
* 返 回 值：void
* 创建日期：2018年01月01日
* 注    意：
*********************************************************************************************************/
void  InitPackUnpack(void)
{
    i16 i;

    s_ptPack.packModuleId = 0; //s_ptPack的模块ID默认为0，即未使用到的ID
    s_ptPack.packHead = 0; //s_ptPack的数据头默认为0
    s_ptPack.packSecondId = 0; //s_ptPack的二级ID默认为0

    for (i = 0; i < 7; i++)
    {
        s_ptPack.arrData[i] = 0; //s_ptPack的6个数据默认为0
    }

    s_ptPack.checkSum = 0;      //s_ptPack的校验和默认为0

    s_iPackLen = 0; //数据包的长度默认为0
    s_iGotPackId = 0; //获取到数据包ID标志默认为0，即尚未获取到有效模块ID
    s_iRestByteNum = 0; //剩余的字节数默认为0 
}

/*********************************************************************************************************
* 函数名称：PackData
* 函数功能：对数据进行打包
* 输入参数：pPT，待打包的数据首地址
* 输出参数：pPT，打包好的数据首地址
* 返 回 值：valid，1-打包成功，0-打包失败
* 创建日期：2018年01月01日
* 注    意：
*********************************************************************************************************/
u8  PackData(StructPCTPackType* pPT)
{
    u8 valid = 0;

    if (pPT->packModuleId < 0x80)              //包ID必须在0x00～0x7F之间
    {
        valid = 1;    //表示模块ID是合法的
        PackWithCheckSum((u8*)pPT);
    }

    return(valid);
}

/*********************************************************************************************************
* 函数名称：UnPackData
* 函数功能：对数据进行解包，返回1表示解析到一个有效包，此时通过调用GetUnPackRslt函数将数据包取走，否则新数
*           据会覆盖解析好的数据包
* 输入参数：data，待解包的数据
* 输出参数：void
* 返 回 值：是否解包成功，1-解包成功，0-解包失败
* 创建日期：2018年01月01日
* 注    意：
*********************************************************************************************************/
u8  UnPackData(u8 data)
{
    u8 findPack = 0;
    u8* pBuf;
    pBuf = (u8*)&s_ptPack;      //pBuf指向s_ptPack，即pBuf和s_ptPack的值是同一个

    if (s_iGotPackId)            //已经接收到包ID
    {
        if (0x80 <= data)          //非模块ID必须大于或等于0X80
        {
            //数据包中的非模块ID从第二个字节开始存储，因为第一个字节是模块ID
            pBuf[s_iPackLen] = data;                 //赋给pBuf[s_iPackLen]，也相当于赋给s_ptPack中对应的成员
            s_iPackLen++;                      //包长自增
            s_iRestByteNum--;                        //剩余字节数自减

            if (0 >= s_iRestByteNum && 10 == s_iPackLen)
            {
                findPack = UnpackWithCheckSum(pBuf);  //接收到完整数据包后尝试解包
                s_iGotPackId = 0;                     //清除获取到包ID标志，即重新判断下一个数据包
            }
        }
        else
        {
            s_iGotPackId = 0;           //表示出错
        }
    }
    else if (data < 0x80)          //当前的数据为包ID
    {
        s_iRestByteNum = 9;          //剩余的包长，即打包好的包长减去1
        s_iPackLen = 1;          //尚未接收到包ID即表示包长为1
        s_ptPack.packModuleId = data; //数据包的ID
        s_iGotPackId = 1;          //表示已经接收到包ID  
    }

    return findPack;                //如果获取到完整的数据包，并解包成功，findPack为1，否则为0
}

/*********************************************************************************************************
* 函数名称：GetUnPackRslt
* 函数功能：获取解包结果，主要看packModuleId、packSecondId和arrData[0]-[5]
* 输入参数：void
* 输出参数：void
* 返 回 值：解包后的结果，packModuleId+packHead+packSecondId+arrData[0]-[5]+checkSum，主要看arrData[0]-[5]
* 创建日期：2018年01月01日
* 注    意：
*********************************************************************************************************/
StructPCTPackType  GetUnPackRslt(void)
{
    return(s_ptPack);
}