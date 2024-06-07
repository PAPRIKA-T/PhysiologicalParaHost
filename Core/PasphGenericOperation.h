#pragma once
#include <QString>
namespace PasphGenericOperation {
	inline const QString SwapBool2QSting(bool ok) {
		if (ok) return QString("True");
		else return QString("False");
	}

	uint16_t CombineData2816(uint8_t high_byte, uint8_t low_byte);
}