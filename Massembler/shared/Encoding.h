#pragma once 

#include <stdint.h>

#include "Buffer.h"

namespace Massembler {

enum class ModType : uint8_t
{
	REG_SIB = 0,
	DISP8 = 1,
	DISP32 = 2,
	REG = 3,
};

#pragma pack(push, 1)
struct ModRM_t
{
	uint8_t rm : 3;
	uint8_t reg : 3;	// Register Index.
	uint8_t mod : 2;
};

struct REXPrefix_t
{
	uint8_t B : 1;                  // Extends MODRM.rm
	uint8_t X : 1;
	uint8_t R : 1;                  // Extends MODRM.reg
	uint8_t W : 1;                  // 64 bit operands
	uint8_t _Dummy : 4;             // Always 0b01000
};
static_assert(sizeof(REXPrefix_t) == 1, "Flawed");

struct Prefix_t
{
	uint8_t Lock : 1;				// F1
	uint8_t Repne : 1;				// F2
	uint8_t Rep : 1;				// F3
	uint8_t CS : 1;					// 2E
	uint8_t SS : 1;					// 36
	uint8_t DS : 1;					// 3E
	uint8_t ES : 1;					// 26
	uint8_t FS : 1;					// 64
	uint8_t GS : 1;					// 65
	uint8_t BranchNotTaken : 1;		// 2E
	uint8_t BranchTaken : 1;		// 3E
	uint8_t OperandSize : 1;		// 66
	uint8_t AddressSize : 1;		// 67
};

#pragma pack(pop)

}
