#include "PasphGenericOperation.h"

uint16_t PasphGenericOperation::CombineData2816(uint8_t high_byte, uint8_t low_byte)
{
	// 将高8位数据左移8位，然后与低8位数据进行按位或操作
	return ((uint16_t)high_byte << 8) | low_byte;
}
