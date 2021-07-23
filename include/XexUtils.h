#pragma once

#include <string>
#include <xtl.h>

namespace XexUtils
{

namespace Formatter
{
	std::string Format(const char* format, ...);

	std::wstring ToWide(const std::string& narrowString);
}

namespace Kernel
{
	extern "C"
	{
		DWORD    __stdcall    ExCreateThread(
			PHANDLE                  pHandle, 
			DWORD                    dwStackSize, 
			LPDWORD                  lpThreadId, 
			VOID*                    apiThreadStartup , 
			LPTHREAD_START_ROUTINE   lpStartAddress, 
			LPVOID                   lpParameter, 
			DWORD                    dwCreationFlagsMod
			);

		VOID    __cdecl        XapiThreadStartup(
			VOID    (__cdecl *StartRoutine)(VOID *), 
			VOID    *StartContext
			);

		DWORD XamGetCurrentTitleId();

		void DbgPrint(const char* s, ...);

		BOOL MmIsAddressValid(PVOID address);

		#define __isync() __emit(0x4C00012C)
	}
}

namespace Math
{
	struct vec2
	{
		vec2() : x(0.0f), y(0.0f) {}
		vec2(float x, float y) : x(x), y(y) {}

		float x;
		float y;

		bool operator==(const vec2& other) const { return x == other.x && y == other.y; }

		vec2 operator+(const vec2& other);
	};
	
	struct vec3
	{
		vec3() : x(0.0f), y(0.0f), z(0.0f) {}
		vec3(float x, float y, float z) : x(x), y(y), z(z) {}

		float x;
		float y;
		float z;

		bool operator==(const vec3& other) const { return x == other.x && y == other.y && z == other.z; }

		vec3 operator+(const vec3& other);
	};

	double Radians(double degrees);

	vec3 ToFront(const vec3& origin, float viewY, float distance);
}

namespace Memory
{
	DWORD ResolveFunction(const std::string& moduleName, DWORD ordinal);

	void Thread(LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameters = 0);

	void PatchInJump(DWORD* address, DWORD destination, BOOL linked);

	void HookFunctionStart(DWORD* address, DWORD* saveStub, DWORD destination);

	DWORD RelinkGPLR(int offset, DWORD* saveStubAddr, DWORD* orgAddr);

	template<typename T>
	void Write(DWORD address, T data)
	{
		if (!Kernel::MmIsAddressValid((DWORD*)address))
		{
			Kernel::DbgPrint("Invalid address: %#010x\n", address);
			return;
		}

		*(T*)address = data;
	}

	template<typename T>
	T Read(DWORD address)
	{
		if (!Kernel::MmIsAddressValid((DWORD*)address))
		{
			Kernel::DbgPrint("Invalid address: %#010x\n", address);
			return 0;
		}

		return *(T*)address;
	}
}

namespace Xam
{
	typedef enum
	{
		XNOTIFYUI_TYPE_FRIENDONLINE = 0,
		XNOTIFYUI_TYPE_GAMEINVITE = 1,
		XNOTIFYUI_TYPE_FRIENDREQUEST = 2,
		XNOTIFYUI_TYPE_GENERIC = 3, // mail icon
		XNOTIFYUI_TYPE_MULTIPENDING = 4,
		XNOTIFYUI_TYPE_PERSONALMESSAGE = 5,
		XNOTIFYUI_TYPE_SIGNEDOUT = 6,
		XNOTIFYUI_TYPE_SIGNEDIN = 7,
		XNOTIFYUI_TYPE_SIGNEDINLIVE = 8,
		XNOTIFYUI_TYPE_SIGNEDINNEEDPASS = 9,
		XNOTIFYUI_TYPE_CHATREQUEST = 10,
		XNOTIFYUI_TYPE_CONNECTIONLOST = 11,
		XNOTIFYUI_TYPE_DOWNLOADCOMPLETE = 12,
		XNOTIFYUI_TYPE_SONGPLAYING = 13, // music icon
		XNOTIFYUI_TYPE_PREFERRED_REVIEW = 14, // happy face icon
		XNOTIFYUI_TYPE_AVOID_REVIEW = 15, // sad face icon
		XNOTIFYUI_TYPE_COMPLAINT = 16, // hammer icon
		XNOTIFYUI_TYPE_CHATCALLBACK = 17,
		XNOTIFYUI_TYPE_REMOVEDMU = 18,
		XNOTIFYUI_TYPE_REMOVEDGAMEPAD = 19,
		XNOTIFYUI_TYPE_CHATJOIN = 20,
		XNOTIFYUI_TYPE_CHATLEAVE = 21,
		XNOTIFYUI_TYPE_GAMEINVITESENT = 22,
		XNOTIFYUI_TYPE_CANCELPERSISTENT = 23,
		XNOTIFYUI_TYPE_CHATCALLBACKSENT = 24,
		XNOTIFYUI_TYPE_MULTIFRIENDONLINE = 25,
		XNOTIFYUI_TYPE_ONEFRIENDONLINE = 26,
		XNOTIFYUI_TYPE_ACHIEVEMENT = 27,
		XNOTIFYUI_TYPE_HYBRIDDISC = 28,
		XNOTIFYUI_TYPE_MAILBOX = 29, // mailbox icon
		XNOTIFYUI_TYPE_VIDEOCHATINVITE = 30,
		XNOTIFYUI_TYPE_DOWNLOADCOMPLETEDREADYTOPLAY = 31,
		XNOTIFYUI_TYPE_CANNOTDOWNLOAD = 32,
		XNOTIFYUI_TYPE_DOWNLOADSTOPPED = 33,
		XNOTIFYUI_TYPE_CONSOLEMESSAGE = 34,
		XNOTIFYUI_TYPE_GAMEMESSAGE = 35,
		XNOTIFYUI_TYPE_DEVICEFULL = 36,
		XNOTIFYUI_TYPE_CHATMESSAGE = 38,
		XNOTIFYUI_TYPE_MULTIACHIEVEMENTS = 39,
		XNOTIFYUI_TYPE_NUDGE = 40,
		XNOTIFYUI_TYPE_MESSENGERCONNECTIONLOST = 41,
		XNOTIFYUI_TYPE_MESSENGERSIGNINFAILED = 43,
		XNOTIFYUI_TYPE_MESSENGERCONVERSATIONMISSED = 44,
		XNOTIFYUI_TYPE_FAMILYTIMERREMAINING = 45,
		XNOTIFYUI_TYPE_CONNECTIONLOSTRECONNECT = 46,
		XNOTIFYUI_TYPE_EXCESSIVEPLAYTIME = 47,
		XNOTIFYUI_TYPE_PARTYJOINREQUEST = 49,
		XNOTIFYUI_TYPE_PARTYINVITESENT = 50,
		XNOTIFYUI_TYPE_PARTYGAMEINVITESENT = 51,
		XNOTIFYUI_TYPE_PARTYKICKED = 52,
		XNOTIFYUI_TYPE_PARTYDISCONNECTED = 53,
		XNOTIFYUI_TYPE_PARTYCANNOTCONNECT = 56,
		XNOTIFYUI_TYPE_PARTYSOMEONEJOINED = 57,
		XNOTIFYUI_TYPE_PARTYSOMEONELEFT = 58,
		XNOTIFYUI_TYPE_GAMERPICTUREUNLOCKED = 59,
		XNOTIFYUI_TYPE_AVATARAWARDUNLOCKED = 60,
		XNOTIFYUI_TYPE_PARTYJOINED = 61,
		XNOTIFYUI_TYPE_REMOVEDUSB = 62,
		XNOTIFYUI_TYPE_PLAYERMUTED = 63,
		XNOTIFYUI_TYPE_PLAYERUNMUTED = 64,
		XNOTIFYUI_TYPE_CHATMESSAGE2 = 65,
		XNOTIFYUI_TYPE_KINECTCONNECTED = 66,
		XNOTIFYUI_TYPE_KINECTBREAK = 67,
		XNOTIFYUI_TYPE_ETHERNET = 68,
		XNOTIFYUI_TYPE_KINECTPLAYERRECOGNIZED = 69,
		XNOTIFYUI_TYPE_CONSOLESHUTTINGDOWNSOONALERT = 70,
		XNOTIFYUI_TYPE_PROFILESIGNEDINELSEWHERE = 71,
		XNOTIFYUI_TYPE_LASTSIGNINELSEWHERE = 73,
		XNOTIFYUI_TYPE_KINECTDEVICEUNSUPPORTED = 74,
		XNOTIFYUI_TYPE_WIRELESSDEVICETURNOFF = 75,
		XNOTIFYUI_TYPE_UPDATING = 76,
		XNOTIFYUI_TYPE_SMARTGLASSAVAILABLE = 77
	} XNOTIFYQUEUEUI_TYPE;

	void XNotifyQueueUI(XNOTIFYQUEUEUI_TYPE exnq, DWORD dwUserIndex, ULONGLONG qwAreas, PWCHAR displayText, PVOID contextData);

	void XNotify(const std::string& text, XNOTIFYQUEUEUI_TYPE type = Xam::XNOTIFYUI_TYPE_PREFERRED_REVIEW);

	std::string ShowKeyboard(const std::string& title, const std::string& description, const std::string& defaultValue, size_t maxLength = 15, DWORD keyboardType = VKBD_DEFAULT);
}
}