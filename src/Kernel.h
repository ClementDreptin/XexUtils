#pragma once

// Most of those were taken from xkelib

struct STRING
{
    uint16_t Length;
    uint16_t MaxLength;
    char *Buffer;
};

struct UNICODE_STRING
{
    uint16_t Length;
    uint16_t MaxLength;
    wchar_t *Buffer;
};

typedef enum _FIRMWARE_REENTRY
{
    HalHaltRoutine,
    HalRebootRoutine,
    HalKdRebootRoutine,
    HalFatalErrorRebootRoutine,
    HalResetSMCRoutine,
    HalPowerDownRoutine,
    HalRebootQuiesceRoutine,
    HalForceShutdownRoutine,
    HalPowerCycleQuiesceRoutine,
    HalMaximumRoutine,
} FIRMWARE_REENTRY;

typedef enum _XNCALLER_TYPE
{
    XNCALLER_INVALID = 0,
    XNCALLER_TITLE = 1,
    XNCALLER_SYSAPP = 2,
    XNCALLER_XBDM = 3,
    XNCALLER_PERSISTING = 3,
    XNCALLER_TEST = 4,
    NUM_XNCALLER_TYPES = 4,
} XNCALLER_TYPE;

struct LDR_DATA_TABLE_ENTRY
{
    LIST_ENTRY InLoadOrderLinks;
    LIST_ENTRY InClosureOrderLinks;
    LIST_ENTRY InInitializationOrderLinks;
    void *NtHeadersBase;
    void *ImageBase;
    uint32_t SizeOfNtImage;
    UNICODE_STRING FullDllName;
    UNICODE_STRING BaseDllName;
    uint32_t Flags;
    uint32_t SizeOfFullImage;
    void *EntryPoint;
    uint16_t LoadCount;
    uint16_t ModuleIndex;
    void *DllBaseOriginal;
    uint32_t CheckSum;
    uint32_t ModuleLoadFlags;
    uint32_t TimeDateStamp;
    void *LoadedImports;
    void *XexHeaderBase;

    union {
        STRING LoadFileName;

        struct
        {
            void *ClosureRoot;
            void *TraversalParent;
        } asEntry;
    } inf;
};

struct XEX_IMPORT_TABLE
{
    uint32_t TableSize;
    uint8_t NextImportDigest[20];
    uint32_t ModuleNumber;
    uint32_t Version[2];
    uint8_t Unused;
    uint8_t ModuleIndex;
    uint16_t ImportCount;
    uint32_t ImportStubAddr[1];
};

struct XEX_IMPORT_DESCRIPTOR
{
    uint32_t Size;
    uint32_t NameTableSize;
    uint32_t ModuleCount;
};

typedef enum _EXCREATETHREAD_FLAG
{
    EXCREATETHREAD_SUSPENDED = 1 << 0,
    EXCREATETHREAD_SYSTEM = 1 << 1,
    EXCREATETHREAD_TLS_STATIC = 1 << 3,
    EXCREATETHREAD_PRIORITY1 = 1 << 5,
    EXCREATETHREAD_PRIORITY0 = 1 << 6,
    EXCREATETHREAD_RETURN_KTHREAD = 1 << 7,
    EXCREATETHREAD_TITLE_EXEC = 1 << 8,
    EXCREATETHREAD_HIDDEN = 1 << 10,
    EXCREATETHREAD_CORE0 = 1 << 24,
    EXCREATETHREAD_CORE1 = 1 << 25,
    EXCREATETHREAD_CORE2 = 1 << 26,
    EXCREATETHREAD_CORE3 = 1 << 27,
    EXCREATETHREAD_CORE4 = 1 << 28,
    EXCREATETHREAD_CORE5 = 1 << 29,
} EXCREATETHREAD_FLAG;

#define __isync() __emit(0x4C00012C)

#define doSync(addr) \
    __dcbst(0, addr); \
    __sync(); \
    __isync()

extern "C"
{
    void RtlInitAnsiString(STRING *pDestinationString, const char *sourceString);

    HRESULT ObCreateSymbolicLink(STRING *pLinkName, STRING *pDevicePath);

    void HalReturnToFirmware(FIRMWARE_REENTRY powerDownMode);

    void HalSendSMCMessage(void *pInput, void *pOutput);

    uint32_t ExCreateThread(
        HANDLE *pHandle,
        uint32_t stackSize,
        uint32_t *pThreadId,
        void *pApiThreadStartup,
        PTHREAD_START_ROUTINE pStartAddress,
        void *pParameter,
        EXCREATETHREAD_FLAG creationFlags
    );

    uint32_t XamGetCurrentTitleId();

    bool MmIsAddressValid(void *pAddress);

    int NetDll_WSAStartupEx(XNCALLER_TYPE xnCaller, uint16_t versionRequested, WSAData *pWSAData, uint32_t versionReq);

    int NetDll_WSACleanup(XNCALLER_TYPE xnCaller);

    int NetDll_XNetStartup(XNCALLER_TYPE xnCaller, const XNetStartupParams *pXNetParams);

    uint32_t NetDll_inet_addr(const char *ipAddress);

    SOCKET NetDll_socket(XNCALLER_TYPE xnCaller, int af, int type, int protocol);

    int NetDll_setsockopt(XNCALLER_TYPE xnCaller, SOCKET s, int level, int optname, const char *optval, int optlen);

    int NetDll_shutdown(XNCALLER_TYPE xnCaller, SOCKET s, int how);

    int NetDll_closesocket(XNCALLER_TYPE xnCaller, SOCKET s);

    int NetDll_connect(XNCALLER_TYPE xnCaller, SOCKET s, const struct sockaddr *name, int namelen);

    int NetDll_send(XNCALLER_TYPE xnc, SOCKET s, const char *buf, int len, int flags);

    int NetDll_recv(XNCALLER_TYPE xnc, SOCKET s, char *buf, int len, int flags);

    void *RtlImageXexHeaderField(void *pXexHeaderBase, uint32_t imageField);

    void *MmGetPhysicalAddress(void *pAddress);
}
