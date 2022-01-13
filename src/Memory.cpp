#include "pch.h"
#include "Memory.h"

#include "Kernel.h"


namespace XexUtils
{

DWORD Memory::ResolveFunction(const std::string &strModuleName, DWORD dwOrdinal)
{
    HMODULE hModule = GetModuleHandle(strModuleName.c_str());

    return (hModule == NULL) ? NULL : reinterpret_cast<DWORD>(GetProcAddress(hModule, reinterpret_cast<const char *>(dwOrdinal)));
}

void Memory::Thread(PTHREAD_START_ROUTINE pStartAddress, void *pParameters)
{
    CreateThread(nullptr, 0, pStartAddress, pParameters, 0, nullptr);
}

void Memory::ThreadEx(LPTHREAD_START_ROUTINE pStartAddress, void *pParameters, DWORD dwCreationFlags)
{
    Kernel::ExCreateThread(nullptr, 0, nullptr, nullptr, pStartAddress, pParameters, dwCreationFlags);
}

void Memory::HookFunctionStart(DWORD *pdwAddress, DWORD *pdwSaveStub, DWORD dwDestination)
{
    if (pdwSaveStub != NULL && pdwAddress != NULL)
    {
        DWORD dwAddrReloc = reinterpret_cast<DWORD>(&pdwAddress[4]);
        DWORD dwWriteBuffer;

        if (dwAddrReloc & 0x8000)
            dwWriteBuffer = 0x3D600000 + (((dwAddrReloc >> 16) & 0xFFFF) + 1);
        else
            dwWriteBuffer = 0x3D600000 + ((dwAddrReloc >> 16) & 0xFFFF);

        pdwSaveStub[0] = dwWriteBuffer;
        dwWriteBuffer = 0x396B0000 + (dwAddrReloc & 0xFFFF);
        pdwSaveStub[1] = dwWriteBuffer;
        dwWriteBuffer = 0x7D6903A6;
        pdwSaveStub[2] = dwWriteBuffer;
    
        for (int i = 0; i < 4; i++)
        {
            if ((pdwAddress[i] & 0x48000003) == 0x48000001)
            {
                dwWriteBuffer = RelinkGPLR((pdwAddress[i] &~ 0x48000003), &pdwSaveStub[i + 3], &pdwAddress[i]);
                pdwSaveStub[i + 3] = dwWriteBuffer;
            }
            else
            {
                dwWriteBuffer = pdwAddress[i];
                pdwSaveStub[i + 3] = dwWriteBuffer;
            }
        }

        dwWriteBuffer = 0x4E800420; // bctr
        pdwSaveStub[7] = dwWriteBuffer;

        __dcbst(0, pdwSaveStub);
        __sync();
        __isync();

        PatchInJump(pdwAddress, dwDestination, FALSE);
    }
}

void Memory::PatchInJump(DWORD *pdwAddress, DWORD dwDestination, bool bLinked)
{
    DWORD dwWriteBuffer;

    if (dwDestination & 0x8000)
        dwWriteBuffer = 0x3D600000 + (((dwDestination >> 16) & 0xFFFF) + 1);
    else
        dwWriteBuffer = 0x3D600000 + ((dwDestination >> 16) & 0xFFFF);

    pdwAddress[0] = dwWriteBuffer;
    dwWriteBuffer = 0x396B0000 + (dwDestination & 0xFFFF);
    pdwAddress[1] = dwWriteBuffer;
    dwWriteBuffer = 0x7D6903A6;
    pdwAddress[2] = dwWriteBuffer;

    if (bLinked)
        dwWriteBuffer = 0x4E800421;
    else
        dwWriteBuffer = 0x4E800420;

    pdwAddress[3] = dwWriteBuffer;

    __dcbst(0, pdwAddress);
    __sync();
    __isync();
}

void __declspec(naked) Memory::GLPR()
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

DWORD Memory::RelinkGPLR(int nOffset, DWORD *pdwSaveStubAddr, DWORD *pdwOrgAddr)
{
    DWORD dwInst = 0, dwRepl;
    DWORD *pdwSaver = reinterpret_cast<DWORD *>(GLPR);

    if (nOffset & 0x2000000)
        nOffset = nOffset | 0xFC000000;

    dwRepl = pdwOrgAddr[nOffset / 4];

    for (int i = 0; i < 20; i++)
    {
        if (dwRepl == pdwSaver[i])
        {
            int nNewOffset = reinterpret_cast<int>(&pdwSaver[i]) - reinterpret_cast<int>(pdwSaveStubAddr);
            dwInst = 0x48000001 | (nNewOffset & 0x3FFFFFC);
        }
    }

    return dwInst;
}

}
