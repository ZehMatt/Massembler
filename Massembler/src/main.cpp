#include <windows.h>
#include <chrono>

#include "Massembler.h"

int main()
{
	using namespace Massembler;

    void *code = VirtualAlloc(0, (1024 * 1024), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    Buffer buffer(code, (1024 * 1024));

	Assembler assembler(buffer);

    Label testLabel = assembler.createLabel();
    assembler.mov(eax, r8d);
    assembler.mov(rax, rcx);
    assembler.mov(eax, eax);
    assembler.mov(eax, 1);
    assembler.mov(edx, -1);
    assembler.mov(ecx, 1);
    assembler.mov(edi, 1);
    assembler.mov(esi, 1);
    assembler.mov(rax, -1);
    assembler.mov(rax, rax);
    assembler.bindLabel(testLabel);
    assembler.mov(eax, edx);
    assembler.mov(ax, dx);
    assembler.mov(al, dl);
    assembler.jmp(testLabel);

    assembler.finalize();

	// Execute generated code.
	((void(*)())code)();

    return 0;
}
