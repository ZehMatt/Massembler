#pragma once

#include "Buffer.h"
#include "Register.h"
#include "Imm.h"
#include "Label.h"
#include "Memory.h"
#include "Encoding.h"

#include <assert.h>

namespace Massembler {

class AssemblerBase 
{
protected:
	struct LabelData_t
	{
		uint32_t offset;
		uint32_t labelId;
	};

	enum class RelocType : uint8_t
	{
		RELATIVE_32,
		RELATIVE_16,
		RELATIVE_8,
		ABSOLUTE_32,
		ABSOLUTE_16,
		ABSOLUTE_8,
	};

	struct RelocEntry_t
	{
		uint32_t labelId;
		RelocType type;
		uint32_t addressOffset;
	};

protected:
    Buffer& m_buffer;

protected:
	std::vector<LabelData_t> m_labels;
	std::vector<RelocEntry_t> m_relocs;

protected:
    constexpr AssemblerBase(Buffer& buffer) 
        : m_buffer(buffer)
    {
    }

	inline bool encodeRexPrefix(Buffer& buffer, const REXPrefix_t& prefix)
	{
		buffer.write(prefix);
		return true;
	}

    inline bool encodeIb(Buffer& buffer, const Imm& imm)
	{
		buffer.write((int8_t)imm.getImmediate());

		return true;
	}

    inline bool encodeIw(Buffer& buffer, const Imm& imm)
	{
		buffer.write((int16_t)imm.getImmediate());

		return true;
	}

    inline bool encodeId(Buffer& buffer, const Imm& imm)
	{
		buffer.write((int32_t)imm.getImmediate());

		return true;
	}

    inline bool encodeIq(Buffer& buffer, const Imm& imm)
	{
		buffer.write((int64_t)imm.getImmediate());

		return true;
	}

    template<size_t INDEX, typename OP>
    constexpr bool evaluateRexWPrefix(REXPrefix_t& rex, const OP&)
    {
        return false;
    }

    template<size_t INDEX, RegisterIndex TRegIndex, bool TExtend, bool TOperandSize, OperandPosition TPos>
    constexpr bool evaluateRexWPrefix(REXPrefix_t& rex, const RegisterImpl<RegisterType::GP, TRegIndex, 64, TExtend, TOperandSize, TPos>&)
    {
        rex.W = 1;
        return true;
    }

    template<size_t INDEX, typename OP>
    constexpr bool evaluateRexExtendPrefix(REXPrefix_t& rex, const OP&)
    {
        return false;
    }

    template<size_t INDEX, RegisterIndex TRegIndex, uint32_t SIZE, bool TOperandSize, OperandPosition TPos>
    constexpr bool evaluateRexExtendPrefix(REXPrefix_t& rex, const RegisterImpl<RegisterType::GP, TRegIndex, SIZE, true, TOperandSize, TPos>&)
    {
        if (INDEX == 0)
            rex.B = 1;
        else
            rex.R = 1;
        return true;
    }

    template<size_t INDEX, typename OP>
    constexpr bool evaluateRexPrefix(REXPrefix_t& rex, const OP& op)
    {
        return evaluateRexWPrefix<INDEX>(rex, op) || evaluateRexExtendPrefix<INDEX>(rex, op);
    }

    template<size_t INDEX, typename A>
    constexpr bool evaluateOperandSizePrefix(const A& op)
    {
        return false;
    }

    template<RegisterIndex TRegIndex, uint32_t SIZE, bool TExtend, OperandPosition TPos>
    constexpr bool evaluateOperandSizePrefix(const RegisterImpl<RegisterType::GP, TRegIndex, SIZE, TExtend, true, TPos>&)
    {
        return true;
    }

    template<typename OP1, typename OP2, typename OP3, typename OP4>
    inline void evaluatePrefixes(const OP1& op1, const OP2& op2, const OP3& op3, const OP4& op4)
    {
        REXPrefix_t rex{};
        if (evaluateRexPrefix<0>(rex, op1) ||
            evaluateRexPrefix<1>(rex, op2) ||
            evaluateRexPrefix<2>(rex, op3) ||
            evaluateRexPrefix<3>(rex, op4))
        {
            rex._Dummy = 0b0100;
            m_buffer.write(rex);
        }
        if (evaluateOperandSizePrefix<0>(op1) ||
            evaluateOperandSizePrefix<1>(op2) ||
            evaluateOperandSizePrefix<2>(op3) ||
            evaluateOperandSizePrefix<3>(op4))
        {
            m_buffer.write(uint8_t(0x66));
        }
    }

protected:
	inline void createReloc(RelocType type, uint32_t labelId, uint32_t offset)
	{
		RelocEntry_t reloc;
		reloc.type = type;
		reloc.labelId = labelId;
		reloc.addressOffset = offset;
		m_relocs.push_back(reloc);
	}

protected:
	// MR
    inline bool operandMR(const Register& op1, const Register& op2)
	{
        ModRM_t modRM;
		modRM.mod = static_cast<uint8_t>(ModType::REG);

		uint8_t regIndex1 = static_cast<uint8_t>(op1.getIndex());
		if (op1.getPosition() == OperandPosition::HIGH)
			regIndex1 += 4;

		modRM.rm = regIndex1 & 7;

		uint8_t regIndex2 = static_cast<uint8_t>(op2.getIndex());
		if (op2.getPosition() == OperandPosition::HIGH)
			regIndex2 += 4;

		modRM.reg = regIndex2 & 7;

		m_buffer.write(modRM);

		return true;
	}

public:

    inline Label createLabel()
	{
		uint32_t labelId = static_cast<uint32_t>(m_labels.size());

		LabelData_t labelData;
		labelData.labelId = labelId;
		labelData.offset = (uint32_t)-1;

		m_labels.push_back(labelData);

		return Label(labelId);
	}

    inline bool bindLabel(const Label& label)
	{
		LabelData_t& labelData = m_labels.at(label.getLabelId());
		assert(labelData.offset == (uint32_t)-1);

		labelData.offset = m_buffer.pos();

		return true;
	}

    inline bool finalize()
	{
        uint64_t baseVA = reinterpret_cast<uint64_t>(m_buffer.data());

		// Fix all reloc things.
		for (auto itr = m_relocs.begin(); itr != m_relocs.end(); itr++)
		{
			const RelocEntry_t& reloc = *itr;
			const LabelData_t& labelData = m_labels.at(reloc.labelId);
			assert(labelData.offset != (uint32_t)-1);

			uint64_t labelVA = baseVA + labelData.offset;
			uint64_t sourceVA = baseVA + reloc.addressOffset;

			switch (reloc.type)
			{
			case RelocType::RELATIVE_32:
			{
				int32_t relative = static_cast<int32_t>(labelVA - (sourceVA + 4));
                m_buffer.seek(reloc.addressOffset, SEEK_SET);
                m_buffer.write(relative);
			}
			break;
			default:
				assert(false);
				break;
			}
		}

		return true;
	}

public:
    inline const void *getData() const
	{
		return m_buffer.data();
	}

    inline uint32_t size() const
	{
		return m_buffer.size();
	}

    void clear()
    {
        m_buffer.clear();
        m_labels.clear();
        m_relocs.clear();
    }
};

}
