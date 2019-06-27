#pragma once 

#include "AssemblerBase.h"

namespace Massembler {

class Assembler : public AssemblerBase
{
public:
    Assembler(Buffer& buffer) : AssemblerBase(buffer)
    {
    }

    template<RegisterIndex TRegIndex1, bool TExtend1, bool TOperandSize1, OperandPosition TPos1,
        RegisterIndex TRegIndex2, bool TExtend2, bool TOperandSize2, OperandPosition TPos2>
    void mov(const RegisterImpl<RegisterType::GP, TRegIndex1, 8, TExtend1, TOperandSize1, TPos1>& dst,
             const RegisterImpl<RegisterType::GP, TRegIndex2, 8, TExtend2, TOperandSize2, TPos2>& src)
    {
        evaluatePrefixes(dst, src, noreg, noreg);
        encodeIb(m_buffer, 0x88);
        operandMR(dst, src);
    }

    template<RegisterIndex TRegIndex1, bool TExtend1, bool TOperandSize1, OperandPosition TPos1, 
             RegisterIndex TRegIndex2, bool TExtend2, bool TOperandSize2, OperandPosition TPos2>
    void mov(const RegisterImpl<RegisterType::GP, TRegIndex1, 16, TExtend1, TOperandSize1, TPos1>& dst, 
             const RegisterImpl<RegisterType::GP, TRegIndex2, 16, TExtend2, TOperandSize2, TPos2>& src)
    {
        evaluatePrefixes(dst, src, noreg, noreg);
        encodeIb(m_buffer, 0x89);
        operandMR(dst, src);
    }

	template<RegisterIndex TRegIndex1, bool TExtend1, bool TOperandSize1, OperandPosition TPos1, 
             RegisterIndex TRegIndex2, bool TExtend2, bool TOperandSize2, OperandPosition TPos2>
    void mov(const RegisterImpl<RegisterType::GP, TRegIndex1, 32, TExtend1, TOperandSize1, TPos1>& dst,
             const RegisterImpl<RegisterType::GP, TRegIndex2, 32, TExtend2, TOperandSize2, TPos2>& src)
	{
		evaluatePrefixes(dst, src, noreg, noreg);
		encodeIb(m_buffer, 0x89);
		operandMR(dst, src);
	}

	template<RegisterIndex TRegIndex1, bool TExtend1, bool TOperandSize1, OperandPosition TPos1, 
             RegisterIndex TRegIndex2, bool TExtend2, bool TOperandSize2, OperandPosition TPos2>
    void mov(const RegisterImpl<RegisterType::GP, TRegIndex1, 64, TExtend1, TOperandSize1, TPos1>& dst,
             const RegisterImpl<RegisterType::GP, TRegIndex2, 64, TExtend2, TOperandSize2, TPos2>& src)
	{
		evaluatePrefixes(dst, src, noreg, noreg);
		encodeIb(m_buffer, 0x89);
		operandMR(dst, src);
	}

    template<RegisterIndex TRegIndex1, bool TExtend1, bool TOperandSize1, OperandPosition TPos1>
    void mov(const RegisterImpl<RegisterType::GP, TRegIndex1, 32, TExtend1, TOperandSize1, TPos1>& dst,
        const Imm imm)
    {
        evaluatePrefixes(dst, noreg, noreg, noreg);
        encodeIb(m_buffer, 0xB8 + (static_cast<uint8_t>(TRegIndex1) & 7));
        encodeId(m_buffer, static_cast<int32_t>(imm.getImmediate()));
    }

    template<RegisterIndex TRegIndex1, bool TExtend1, bool TOperandSize1, OperandPosition TPos1>
    void mov(const RegisterImpl<RegisterType::GP, TRegIndex1, 64, TExtend1, TOperandSize1, TPos1>& dst,
        const Imm imm)
    {
        evaluatePrefixes(dst, noreg, noreg, noreg);
        encodeIb(m_buffer, 0xB8 + (static_cast<uint8_t>(TRegIndex1) & 7));
        encodeIq(m_buffer, imm.getImmediate());
    }

    void jmp(const Label& label)
	{
		LabelData_t& labelData = m_labels.at(label.getLabelId());

		createReloc(RelocType::RELATIVE_32, label.getLabelId(), m_buffer.pos() + 1);

		// We use always long jmp for now.
		encodeIb(m_buffer, 0xE9);
		encodeId(m_buffer, 0);
	}

};

}
