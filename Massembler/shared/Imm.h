#pragma once

#include <algorithm>

#include "Operand.h"

namespace Massembler {

class Imm : public Operand
{
private:
	const int64_t m_imm;

public:
	constexpr Imm(int64_t imm) : Operand(OperandType::IMM, 64),
        m_imm(imm)
	{
	}
    constexpr Imm(int32_t imm) : Operand(OperandType::IMM, 32),
        m_imm(imm)
    {
    }
    constexpr Imm(int16_t imm) : Operand(OperandType::IMM, 16),
        m_imm(imm)
    {
    }
    constexpr Imm(int8_t imm) : Operand(OperandType::IMM, 8),
        m_imm(imm)
    {
    }

	int64_t getImmediate() const
	{
		return m_imm;
	}

	uint32_t getImmByteSize() const
	{
		int64_t v = std::abs(m_imm);

		size_t bits = 0;
		while (v > 0)
		{
			v <<= 1;
			bits++;
		}

		if (bits > 32)
			return 8;
		else if (bits > 16)
			return 4;
		else if (bits > 8)
			return 2;

		return 1;
	}
};

}
