#pragma once 

#include "Operand.h"

namespace Massembler {

enum class RegisterType : uint8_t 
{
	NONE = 0,
	GP,
	ST,
	CR,
	DR,
	MM,
	MMX,
	SEG,
	XMM,
	YMM,
};

enum class RegisterIndex : uint8_t
{
	INDEX0 = 0,
	INDEX1,
	INDEX2,
	INDEX3,
	INDEX4,
	INDEX5,
	INDEX6,
	INDEX7,
	INDEX8,
	INDEX9,
	INDEX10,
	INDEX11,
	INDEX12,
	INDEX13,
	INDEX14,
	INDEX15,
	NONE,
};

class Register : public Operand
{
    const RegisterType _registerType;
    const RegisterIndex _registerIndex;
    const bool _extend;
    const bool _operandSize;
    const OperandPosition _pos;

public:
    constexpr Register(const RegisterType registerType,
        const RegisterIndex registerIndex,
        const uint32_t size,
        const bool extend,
        const bool operandSize,
        const OperandPosition pos) :
            Operand(OperandType::REGISTER, size),
            _registerType(registerType),
            _registerIndex(registerIndex),
            _extend(extend),
            _operandSize(operandSize),
            _pos(pos)
    {
    }
    RegisterType getType() const
    {
        return _registerType;
    }
    RegisterIndex getIndex() const
    {
        return _registerIndex;
    }
    OperandPosition getPosition() const
    {
        return _pos;
    }
};

template<RegisterType TYPE, RegisterIndex INDEX, uint32_t SIZE, bool TExtend = false, bool TOperandSize = false, OperandPosition TPos = OperandPosition::LOW>
class RegisterImpl : public Register
{
public:
    constexpr RegisterImpl() 
        : Register(TYPE, INDEX, SIZE, TExtend, TOperandSize, TPos)
    {
    }
};

// Empty reg.
static constexpr RegisterImpl<RegisterType::NONE, RegisterIndex::NONE, 0> noreg;

static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX0, 8> al;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX1, 8> cl;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX2, 8> dl;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX3, 8> bl;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX4, 8> spl;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX5, 8> bpl;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX6, 8> sil;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX7, 8> dil;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX8, 8, true, true> r8b;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX9, 8, true, true> r9b;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX10, 8, true, true> r10b;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX11, 8, true, true> r11b;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX12, 8, true, true> r12b;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX13, 8, true, true> r13b;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX14, 8, true, true> r14b;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX15, 8, true, true> r15b;

static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX0, 8, false, false, OperandPosition::HIGH> ah;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX1, 8, false, false, OperandPosition::HIGH> ch;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX2, 8, false, false, OperandPosition::HIGH> dh;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX3, 8, false, false, OperandPosition::HIGH> bh;

static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX0, 16, false, true> ax;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX1, 16, false, true> cx;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX2, 16, false, true> dx;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX3, 16, false, true> bx;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX4, 16, false, true> sp;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX5, 16, false, true> bp;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX6, 16, false, true> si;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX7, 16, false, true> di;

static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX0, 16, true, true> r8w;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX1, 16, true, true> r9w;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX2, 16, true, true> r10w;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX3, 16, true, true> r11w;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX4, 16, true, true> r12w;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX5, 16, true, true> r13w;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX6, 16, true, true> r14w;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX7, 16, true, true> r15w;

static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX0, 32> eax;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX1, 32> ecx;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX2, 32> edx;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX3, 32> ebx;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX4, 32> esp;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX5, 32> ebp;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX6, 32> esi;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX7, 32> edi;

static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX8, 32, true, false> r8d;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX9, 32, true, false> r9d;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX10, 32, true, false> r10d;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX11, 32, true, false> r11d;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX12, 32, true, false> r12d;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX13, 32, true, false> r13d;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX14, 32, true, false> r14d;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX15, 32, true, false> r15d;

static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX0, 64> rax;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX1, 64> rcx;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX2, 64> rdx;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX3, 64> rbx;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX4, 64> rsp;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX5, 64> rbp;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX6, 64> rsi;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX7, 64> rdi;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX8, 64, true>  r8;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX9, 64, true>  r9;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX10, 64, true> r10;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX11, 64, true> r11;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX12, 64, true> r12;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX13, 64, true> r13;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX14, 64, true> r14;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX15, 64, true> r15;

static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX0, 0> zax;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX1, 0> zcx;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX2, 0> zdx;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX3, 0> zbx;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX4, 0> zsp;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX5, 0> zbp;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX6, 0> zsi;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX7, 0> zdi;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX8, 0>  z8;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX9, 0>  z9;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX10, 0> z10;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX11, 0> z11;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX12, 0> z12;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX13, 0> z13;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX14, 0> z14;
static constexpr RegisterImpl<RegisterType::GP, RegisterIndex::INDEX15, 0> z15;

static constexpr RegisterImpl<RegisterType::ST, RegisterIndex::INDEX0, 64> st0;
static constexpr RegisterImpl<RegisterType::ST, RegisterIndex::INDEX1, 64> st1;
static constexpr RegisterImpl<RegisterType::ST, RegisterIndex::INDEX2, 64> st2;
static constexpr RegisterImpl<RegisterType::ST, RegisterIndex::INDEX3, 64> st3;
static constexpr RegisterImpl<RegisterType::ST, RegisterIndex::INDEX4, 64> st4;
static constexpr RegisterImpl<RegisterType::ST, RegisterIndex::INDEX5, 64> st5;
static constexpr RegisterImpl<RegisterType::ST, RegisterIndex::INDEX6, 64> st6;
static constexpr RegisterImpl<RegisterType::ST, RegisterIndex::INDEX7, 64> st7;

static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX0, 32> cr0;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX1, 32> cr1;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX2, 32> cr2;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX3, 32> cr3;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX4, 32> cr4;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX5, 32> cr5;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX6, 32> cr6;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX7, 32> cr7;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX8, 32> cr8;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX8, 32> cr9;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX10, 32> cr10;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX11, 32> cr11;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX12, 32> cr12;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX13, 32> cr13;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX14, 32> cr14;
static constexpr RegisterImpl<RegisterType::CR, RegisterIndex::INDEX15, 32> cr15;

static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX0, 32> dr0;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX1, 32> dr1;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX2, 32> dr2;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX3, 32> dr3;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX4, 32> dr4;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX5, 32> dr5;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX6, 32> dr6;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX7, 32> dr7;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX8, 32> dr8;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX8, 32> dr9;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX10, 32> dr10;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX11, 32> dr11;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX12, 32> dr12;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX13, 32> dr13;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX14, 32> dr14;
static constexpr RegisterImpl<RegisterType::DR, RegisterIndex::INDEX15, 32> dr15;

static constexpr RegisterImpl<RegisterType::MMX, RegisterIndex::INDEX0, 64> mm0;
static constexpr RegisterImpl<RegisterType::MMX, RegisterIndex::INDEX1, 64> mm1;
static constexpr RegisterImpl<RegisterType::MMX, RegisterIndex::INDEX2, 64> mm2;
static constexpr RegisterImpl<RegisterType::MMX, RegisterIndex::INDEX3, 64> mm3;
static constexpr RegisterImpl<RegisterType::MMX, RegisterIndex::INDEX4, 64> mm4;
static constexpr RegisterImpl<RegisterType::MMX, RegisterIndex::INDEX5, 64> mm5;
static constexpr RegisterImpl<RegisterType::MMX, RegisterIndex::INDEX6, 64> mm6;
static constexpr RegisterImpl<RegisterType::MMX, RegisterIndex::INDEX7, 64> mm7;

static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX0, 128> xmm0;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX1, 128> xmm1;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX2, 128> xmm2;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX3, 128> xmm3;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX4, 128> xmm4;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX5, 128> xmm5;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX6, 128> xmm6;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX7, 128> xmm7;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX8, 128> xmm8;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX9, 128> xmm9;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX10, 128> xmm10;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX11, 128> xmm11;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX12, 128> xmm12;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX13, 128> xmm13;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX14, 128> xmm14;
static constexpr RegisterImpl<RegisterType::XMM, RegisterIndex::INDEX15, 128> xmm15;

static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX0, 256> ymm0;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX1, 256> ymm1;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX2, 256> ymm2;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX3, 256> ymm3;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX4, 256> ymm4;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX5, 256> ymm5;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX6, 256> ymm6;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX7, 256> ymm7;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX8, 256> ymm8;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX9, 256> ymm9;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX10, 256> ymm10;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX11, 256> ymm11;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX12, 256> ymm12;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX13, 256> ymm13;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX14, 256> ymm14;
static constexpr RegisterImpl<RegisterType::YMM, RegisterIndex::INDEX15, 256> ymm15;

}
