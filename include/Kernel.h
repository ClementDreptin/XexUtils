#pragma once

namespace XexUtils
{
namespace Kernel
{
	extern "C"
	{
		DWORD __stdcall ExCreateThread(
			PHANDLE pHandle,
			DWORD dwStackSize,
			LPDWORD lpThreadId,
			PVOID apiThreadStartup,
			LPTHREAD_START_ROUTINE lpStartAddress,
			LPVOID lpParameter,
			DWORD dwCreationFlagsMod
		);

		DWORD XamGetCurrentTitleId();

		void DbgPrint(const char* s, ...);

		BOOL MmIsAddressValid(PVOID address);

		#define __isync() __emit(0x4C00012C)
	}
}
}