#include "pch.h"
#include "Memory.h"

#include "Kernel.h"


namespace XexUtils
{

DWORD Memory::ResolveFunction(CONST std::string& strModuleName, DWORD dwOrdinal)
{
    HMODULE hModule = GetModuleHandle(strModuleName.c_str());

    return (hModule == NULL) ? NULL : (DWORD)GetProcAddress(hModule, (LPCSTR)dwOrdinal);
}

VOID Memory::Thread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameters)
{
    CreateThread(nullptr, 0, lpStartAddress, lpParameters, NULL, NULL);
}

VOID Memory::ThreadEx(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameters, DWORD dwCreationFlags)
{
    Kernel::ExCreateThread(nullptr, 0, nullptr, nullptr, lpStartAddress, lpParameters, dwCreationFlags);
}

VOID Memory::HookFunctionStart(LPDWORD lpdwAddress, LPDWORD lpdwSaveStub, DWORD dwDestination)
{
    if (lpdwSaveStub != NULL && lpdwAddress != NULL)
    {
        DWORD dwAddrReloc = (DWORD)(&lpdwAddress[4]);
        DWORD dwWriteBuffer;

        if (dwAddrReloc & 0x8000)
            dwWriteBuffer = 0x3D600000 + (((dwAddrReloc >> 16) & 0xFFFF) + 1);
        else
            dwWriteBuffer = 0x3D600000 + ((dwAddrReloc >> 16) & 0xFFFF);

        lpdwSaveStub[0] = dwWriteBuffer;
        dwWriteBuffer = 0x396B0000 + (dwAddrReloc & 0xFFFF);
        lpdwSaveStub[1] = dwWriteBuffer;
        dwWriteBuffer = 0x7D6903A6;
        lpdwSaveStub[2] = dwWriteBuffer;
    
        for (INT i = 0; i < 4; i++)
        {
            if ((lpdwAddress[i] & 0x48000003) == 0x48000001)
            {
                dwWriteBuffer = RelinkGPLR((lpdwAddress[i] &~ 0x48000003), &lpdwSaveStub[i + 3], &lpdwAddress[i]);
                lpdwSaveStub[i + 3] = dwWriteBuffer;
            }
            else
            {
                dwWriteBuffer = lpdwAddress[i];
                lpdwSaveStub[i + 3] = dwWriteBuffer;
            }
        }

        dwWriteBuffer = 0x4E800420; // bctr
        lpdwSaveStub[7] = dwWriteBuffer;

        __dcbst(0, lpdwSaveStub);
        __sync();
        __isync();

        PatchInJump(lpdwAddress, dwDestination, FALSE);
    }
}

VOID Memory::PatchInJump(LPDWORD lpdwAddress, DWORD dwDestination, BOOL bLinked)
{
    DWORD dwWriteBuffer;

    if (dwDestination & 0x8000)
        dwWriteBuffer = 0x3D600000 + (((dwDestination >> 16) & 0xFFFF) + 1);
    else
        dwWriteBuffer = 0x3D600000 + ((dwDestination >> 16) & 0xFFFF);

    lpdwAddress[0] = dwWriteBuffer;
    dwWriteBuffer = 0x396B0000 + (dwDestination & 0xFFFF);
    lpdwAddress[1] = dwWriteBuffer;
    dwWriteBuffer = 0x7D6903A6;
    lpdwAddress[2] = dwWriteBuffer;

    if (bLinked)
        dwWriteBuffer = 0x4E800421;
    else
        dwWriteBuffer = 0x4E800420;

    lpdwAddress[3] = dwWriteBuffer;

    __dcbst(0, lpdwAddress);
    __sync();
    __isync();
}

VOID __declspec(naked) Memory::GLPR()
{
    __asm
    {
        std     r14, -0x98(sp)
        std     r15, -0x90(sp)
        std     r16, -0x88(sp)
        std     r17, -0x80(sp)
        std     r18, -0x78(sp)
        std     r19, -0x70(sp)
        std     r20, -0x68(sp)
        std     r21, -0x60(sp)
        std     r22, -0x58(sp)
        std     r23, -0x50(sp)
        std     r24, -0x48(sp)
        std     r25, -0x40(sp)
        std     r26, -0x38(sp)
        std     r27, -0x30(sp)
        std     r28, -0x28(sp)
        std     r29, -0x20(sp)
        std     r30, -0x18(sp)
        std     r31, -0x10(sp)
        stw     r12, -0x8(sp)
        blr
    }
}

DWORD Memory::RelinkGPLR(INT nOffset, LPDWORD lpdwSaveStubAddr, LPDWORD lpdwOrgAddr)
{
    DWORD dwInst = 0, dwRepl;
    LPDWORD lpdwSaver = (LPDWORD)GLPR;

    if (nOffset & 0x2000000)
        nOffset = nOffset | 0xFC000000;

    dwRepl = lpdwOrgAddr[nOffset / 4];

    for (INT i = 0; i < 20; i++)
    {
        if (dwRepl == lpdwSaver[i])
        {
            INT nNewOffset = (INT)&lpdwSaver[i] - (INT)lpdwSaveStubAddr;
            dwInst = 0x48000001 | (nNewOffset & 0x3FFFFFC);
        }
    }

    return dwInst;
}

}
