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

typedef enum _PROC_TYPE
{
    PROC_IDLE,
    PROC_USER,
    PROC_SYSTEM,
} PROC_TYPE;

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

typedef enum _XEX_LOADING_FLAG
{
    XEX_LOADING_FLAG_TITLE_PROCESS = 1 << 0,
    XEX_LOADING_FLAG_TITLE_IMPORTS = 1 << 1,
    XEX_LOADING_FLAG_DEBUGGER = 1 << 2,
    XEX_LOADING_FLAG_DLL = 1 << 3,
    XEX_LOADING_FLAG_PATCH = 1 << 4,
    XEX_LOADING_FLAG_PATCH_FULL = 1 << 5,
    XEX_LOADING_FLAG_PATCH_DELTA = 1 << 6,
    XEX_LOADING_FLAG_BOUND_PATH = 1 << 30,
    XEX_LOADING_FLAG_SILENT_LOAD = 1 << 31,
    XEX_LOADING_TYPE_TITLE = XEX_LOADING_FLAG_TITLE_PROCESS,
    XEX_LOADING_TYPE_TITLE_DLL = XEX_LOADING_FLAG_TITLE_PROCESS | XEX_LOADING_FLAG_DLL,
    XEX_LOADING_TYPE_SYSTEM_APP = XEX_LOADING_FLAG_DLL,
    XEX_LOADING_TYPE_SYSTEM_DLL = XEX_LOADING_FLAG_DLL | XEX_LOADING_FLAG_TITLE_IMPORTS,
} XEX_LOADING_FLAG;

#define __isync() __emit(0x4C00012C)

#define doSync(addr) \
    __dcbst(0, addr); \
    __sync(); \
    __isync()

extern "C"
{
    uint32_t ExCreateThread(
        HANDLE *pHandle,
        uint32_t stackSize,
        uint32_t *pThreadId,
        void *pApiThreadStartup,
        PTHREAD_START_ROUTINE pStartAddress,
        void *pParameter,
        EXCREATETHREAD_FLAG creationFlags
    );

    void HalReturnToFirmware(FIRMWARE_REENTRY powerDownMode);

    void HalSendSMCMessage(void *pInput, void *pOutput);

    PROC_TYPE KeGetCurrentProcessType();

    void *MmGetPhysicalAddress(void *pAddress);

    bool MmIsAddressValid(void *pAddress);

    int NetDll_WSACleanup(XNCALLER_TYPE xnCaller);

    int NetDll_WSAStartupEx(XNCALLER_TYPE xnCaller, uint16_t versionRequested, WSAData *pWSAData, uint32_t versionReq);

    int NetDll_XNetStartup(XNCALLER_TYPE xnCaller, const XNetStartupParams *pXNetParams);

    int NetDll_closesocket(XNCALLER_TYPE xnCaller, SOCKET s);

    int NetDll_connect(XNCALLER_TYPE xnCaller, SOCKET s, const struct sockaddr *name, int namelen);

    uint32_t NetDll_inet_addr(const char *ipAddress);

    int NetDll_recv(XNCALLER_TYPE xnc, SOCKET s, char *buf, int len, int flags);

    int NetDll_send(XNCALLER_TYPE xnc, SOCKET s, const char *buf, int len, int flags);

    int NetDll_setsockopt(XNCALLER_TYPE xnCaller, SOCKET s, int level, int optname, const char *optval, int optlen);

    int NetDll_shutdown(XNCALLER_TYPE xnCaller, SOCKET s, int how);

    SOCKET NetDll_socket(XNCALLER_TYPE xnCaller, int af, int type, int protocol);

    HRESULT ObCreateSymbolicLink(STRING *pLinkName, STRING *pDevicePath);

    void *RtlImageXexHeaderField(void *pXexHeaderBase, uint32_t imageField);

    void RtlInitAnsiString(STRING *pDestinationString, const char *sourceString);

    uint32_t XamGetCurrentTitleId();

    HRESULT XexLoadImage(const char *imageName, XEX_LOADING_FLAG flags, uint32_t minVersion, HANDLE *pHandle);

    HRESULT XexUnloadImage(HANDLE handle);
}
