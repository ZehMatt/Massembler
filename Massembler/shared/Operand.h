#pragma once

#include <stdint.h>

namespace Massembler {

enum class OperandPosition : uint8_t
{
	LOW = 0,
	HIGH = 1,
};

enum class OperandType : uint8_t
{
	IMM = 0,
	REGISTER = 1,
	MEMORY = 2,
};

class Operand
{
    const OperandType _operandType;
    const uint16_t _operandSize;

public:
    constexpr Operand(OperandType operandType, uint16_t size) 
        : _operandType(operandType), 
        _operandSize(size)
    {}

    OperandType getOperandType() const
    {
        return _operandType;
    }
};

}
