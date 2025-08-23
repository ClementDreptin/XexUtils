#pragma once

/// @file Kernel.h
///
/// A list of functions exported by `xboxkrnl.exe` and `xam.xex` and the associated
/// structures to use them. Most of those were taken from xkelib.

typedef long NTSTATUS;

// Found here:
// https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-erref/596a1078-e883-4972-9bbc-49e60bebca55
#define STATUS_OBJECT_NAME_COLLISION 0xC0000035

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

#define EXPORTNUM(module, x)

// Disable the C4201 warning for nameless union/struct
#pragma warning(push)
#pragma warning(disable : 4201)

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
        };
    };
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

#pragma pack(push, 1)

union XBOX32VER {
    struct
    {
        uint8_t Major : 4;
        uint8_t Minor : 4;
        uint16_t Build;
        uint8_t Qfe;
    };

    uint32_t asULong;
};

#pragma pack(pop)

struct XEX_EXECUTION_ID
{
    uint32_t MediaId;
    XBOX32VER Version;
    XBOX32VER BaseVersion;

    union {
        uint32_t TitleId;

        struct
        {
            uint16_t PublisherId;
            uint16_t GameId;
        };
    };

    uint8_t Platform;
    uint8_t ExecutableType;
    uint8_t DiscNum;
    uint8_t DiscsInSet;
    uint32_t SaveGameId;
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

struct OBJECT_ATTRIBUTES
{
    HANDLE RootDirectory;
    STRING *ObjectName;
    uint32_t Attributes;
};

struct IO_STATUS_BLOCK
{
    union {
        NTSTATUS Status;
        void *Pointer;
    };

    uintptr_t Information;
};

#define InitializeObjectAttributes(p, name, attrib, root) \
    { \
        (p)->RootDirectory = root; \
        (p)->Attributes = attrib; \
        (p)->ObjectName = name; \
    }

typedef enum _XEX_HEADER_FIELD
{
    XEX_HEADER_IMPORT_DESCRIPTOR = 0x103FF,
    XEX_HEADER_EXECUTION_ID = 0x40006
} XEX_HEADER_FIELD;

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

struct KEXCEPTION_FRAME
{
    uint32_t Status;
    uint32_t Unknown1;
    uint32_t Unknown2;
    uint32_t Unknown3;
    BOOL Continuable;
    uint32_t ExceptionInformation[32];
};

typedef BOOL (*TRAPHANDLER)(void *pUnknown, KEXCEPTION_FRAME *pExceptionFrame, CONTEXT *pContext, BOOL secondChance);

#pragma warning(pop) // Disable C4201

#define __isync() __emit(0x4C00012C)

#define doSync(addr) \
    __dcbst(0, addr); \
    __sync(); \
    __isync()

extern "C"
{
    EXPORTNUM("xboxkrnl.exe", 13)
    uint32_t ExCreateThread(
        HANDLE *pHandle,
        uint32_t stackSize,
        uint32_t *pThreadId,
        void *pApiThreadStartup,
        PTHREAD_START_ROUTINE pStartAddress,
        void *pParameter,
        EXCREATETHREAD_FLAG creationFlags
    );

    EXPORTNUM("xboxkrnl.exe", 40)
    void HalReturnToFirmware(
        FIRMWARE_REENTRY powerDownMode
    );

    EXPORTNUM("xboxkrnl.exe", 41)
    void HalSendSMCMessage(
        void *pInput,
        void *pOutput
    );

    EXPORTNUM("xboxkrnl.exe", 102)
    PROC_TYPE KeGetCurrentProcessType(
        void
    );

    EXPORTNUM("xboxkrnl.exe", 190)
    void *MmGetPhysicalAddress(
        void *pAddress
    );

    EXPORTNUM("xboxkrnl.exe", 191)
    bool MmIsAddressValid(
        void *pAddress
    );

    EXPORTNUM("xam.xex", 14)
    SOCKET NetDll_accept(
        XNCALLER_TYPE xnCaller,
        SOCKET s,
        sockaddr *addr,
        int *addrlen
    );

    EXPORTNUM("xam.xex", 11)
    int NetDll_bind(
        XNCALLER_TYPE xnCaller,
        SOCKET s,
        const sockaddr *name,
        int namelen
    );

    EXPORTNUM("xam.xex", 4)
    int NetDll_closesocket(
        XNCALLER_TYPE xnCaller,
        SOCKET s
    );

    EXPORTNUM("xam.xex", 12)
    int NetDll_connect(
        XNCALLER_TYPE xnCaller,
        SOCKET s,
        const sockaddr *name,
        int namelen
    );

    EXPORTNUM("xam.xex", 10)
    int NetDll_getpeername(
        XNCALLER_TYPE xnc,
        SOCKET s,
        sockaddr *name,
        int *namelen
    );

    EXPORTNUM("xam.xex", 9)
    int NetDll_getsockname(
        XNCALLER_TYPE xnCaller,
        SOCKET s,
        sockaddr *name,
        int *namelen
    );

    EXPORTNUM("xam.xex", 8)
    int NetDll_getsockopt(
        XNCALLER_TYPE xnCaller,
        SOCKET s,
        int level,
        int optname,
        char *optval,
        int *optlen
    );

    EXPORTNUM("xam.xex", 26)
    uint32_t NetDll_inet_addr(
        const char *cp
    );

    EXPORTNUM("xam.xex", 6)
    int NetDll_ioctlsocket(
        XNCALLER_TYPE xnCaller,
        SOCKET s,
        int cmd,
        uint32_t *argp
    );

    EXPORTNUM("xam.xex", 13)
    int NetDll_listen(
        XNCALLER_TYPE xnCaller,
        SOCKET s,
        int backlog
    );

    EXPORTNUM("xam.xex", 18)
    int NetDll_recv(
        XNCALLER_TYPE xnCaller,
        SOCKET s,
        char *buf,
        int len,
        int flags
    );

    EXPORTNUM("xam.xex", 20)
    int NetDll_recvfrom(
        XNCALLER_TYPE xnCaller,
        SOCKET s,
        const char *buf,
        int len,
        int flags,
        sockaddr *from,
        int *fromlen
    );

    EXPORTNUM("xam.xex", 15)
    int NetDll_select(
        IN XNCALLER_TYPE xnCaller,
        int nfds,
        fd_set *readfds,
        fd_set *writefds,
        fd_set *exceptfds,
        const timeval *timeout
    );

    EXPORTNUM("xam.xex", 22)
    int NetDll_send(
        XNCALLER_TYPE xnCaller,
        SOCKET s,
        const char *buf,
        int len,
        int flags
    );

    EXPORTNUM("xam.xex", 24)
    int NetDll_sendto(
        XNCALLER_TYPE xnCaller,
        SOCKET s,
        const char *buf,
        int len,
        int flags,
        const sockaddr *to,
        int tolen
    );

    EXPORTNUM("xam.xex", 7)
    int NetDll_setsockopt(
        XNCALLER_TYPE xnCaller,
        SOCKET s,
        int level,
        int optname,
        const char *optval,
        int optlen
    );

    EXPORTNUM("xam.xex", 5)
    int NetDll_shutdown(
        XNCALLER_TYPE xnCaller,
        SOCKET s,
        int how
    );

    EXPORTNUM("xam.xex", 3)
    SOCKET NetDll_socket(
        XNCALLER_TYPE xnCaller,
        int af,
        int type,
        int protocol
    );

    EXPORTNUM("xam.xex", 2)
    int NetDll_WSACleanup(
        XNCALLER_TYPE xnCaller
    );

    EXPORTNUM("xam.xex", 36)
    int NetDll_WSAStartupEx(
        XNCALLER_TYPE xnCaller,
        uint16_t versionRequested,
        WSAData *pWSAData,
        uint32_t versionReq
    );

    EXPORTNUM("xam.xex", 52)
    int NetDll_XNetCleanup(
        XNCALLER_TYPE xnCaller
    );

    EXPORTNUM("xam.xex", 67)
    int NetDll_XNetDnsLookup(
        XNCALLER_TYPE xnCaller,
        const char *pszHost,
        HANDLE hEvent,
        XNDNS **ppxndns
    );

    EXPORTNUM("xam.xex", 68)
    int NetDll_XNetDnsRelease(
        XNCALLER_TYPE xnCaller,
        XNDNS *pxndns
    );

    EXPORTNUM("xam.xex", 51)
    int NetDll_XNetStartup(
        XNCALLER_TYPE xnCaller,
        const XNetStartupParams *pxnsp
    );

    EXPORTNUM("xboxkrnl.exe", 207)
    NTSTATUS NtClose(
        HANDLE Handle
    );

    EXPORTNUM("xboxkrnl.exe", 210)
    NTSTATUS NtCreateFile(
        HANDLE *pHandle,
        ACCESS_MASK desiredAccess,
        OBJECT_ATTRIBUTES *pObjectAttributes,
        IO_STATUS_BLOCK *pIoStatusBlock,
        LARGE_INTEGER *pAllocationSize,
        uint32_t fileAttributes,
        uint32_t shareAccess,
        uint32_t createDisposition,
        uint32_t createOptions
    );

    EXPORTNUM("xboxkrnl.exe", 223)
    NTSTATUS NtOpenFile(
        HANDLE *pHandle,
        ACCESS_MASK desiredAccess,
        OBJECT_ATTRIBUTES *pObjectAttributes,
        IO_STATUS_BLOCK *pIoStatusBlock,
        uint32_t shareAccess,
        uint32_t openOptions
    );

    EXPORTNUM("xboxkrnl.exe", 240)
    NTSTATUS NtReadFile(
        HANDLE handle,
        HANDLE event,
        void *pApcRoutine,
        void *pApcContext,
        IO_STATUS_BLOCK *pIoStatusBlock,
        void *buffer,
        uint32_t length,
        LARGE_INTEGER *pByteOffset
    );

    EXPORTNUM("xboxkrnl.exe", 255)
    NTSTATUS NtWriteFile(
        HANDLE handle,
        HANDLE event,
        void *pApcRoutine,
        void *pApcContext,
        IO_STATUS_BLOCK *pIoStatusBlock,
        void *buffer,
        uint32_t length,
        LARGE_INTEGER *pByteOffset
    );

    EXPORTNUM("xboxkrnl.exe", 259)
    HRESULT ObCreateSymbolicLink(
        STRING *pLinkName,
        STRING *pDevicePath
    );

    EXPORTNUM("xboxkrnl.exe", 299)
    void *RtlImageXexHeaderField(
        void *pXexHeaderBase,
        XEX_HEADER_FIELD imageField
    );

    EXPORTNUM("xboxkrnl.exe", 300)
    void RtlInitAnsiString(
        STRING *pDestinationString,
        const char *sourceString
    );

    EXPORTNUM("xam.xex", 463)
    uint32_t XamGetCurrentTitleId(
        void
    );

    EXPORTNUM("xboxkrnl.exe", 394)
    void XeCryptRandom(
        uint8_t *pBytes,
        size_t count
    );

    EXPORTNUM("xboxkrnl.exe", 409)
    HRESULT XexLoadImage(
        const char *imageName,
        XEX_LOADING_FLAG flags,
        uint32_t minVersion,
        HANDLE *pHandle
    );

    EXPORTNUM("xboxkrnl.exe", 417)
    HRESULT XexUnloadImage(
        HANDLE handle
    );
}
