#pragma once

// Most of those were taken from xkelib

extern "C"
{
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

    void RtlInitAnsiString(STRING *pDestinationString, const char *sourceString);

    HRESULT ObCreateSymbolicLink(STRING *pLinkName, STRING *pDevicePath);

    typedef enum
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

    void HalReturnToFirmware(FIRMWARE_REENTRY powerDownMode);

    void HalSendSMCMessage(void *pInput, void *pOutput);

    DWORD ExCreateThread(
        HANDLE *pHandle,
        DWORD dwStackSize,
        DWORD *pThreadId,
        void *apiThreadStartup,
        PTHREAD_START_ROUTINE pStartAddress,
        void *pParameter,
        DWORD dwCreationFlagsMod
    );

    DWORD XamGetCurrentTitleId();

    bool MmIsAddressValid(void *pAddress);

    typedef enum
    {
        XNCALLER_INVALID = 0,
        XNCALLER_TITLE = 1,
        XNCALLER_SYSAPP = 2,
        XNCALLER_XBDM = 3,
        XNCALLER_PERSISTING = 3,
        XNCALLER_TEST = 4,
        NUM_XNCALLER_TYPES = 4,
    } XNCALLER_TYPE;

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

    struct LDR_DATA_TABLE_ENTRY
    {
        LIST_ENTRY InLoadOrderLinks;           // 0x00 sz:0x8
        LIST_ENTRY InClosureOrderLinks;        // 0x08 sz:0x8
        LIST_ENTRY InInitializationOrderLinks; // 0x10 sz:0x8
        void *NtHeadersBase;                   // 0x18 sz:0x4
        void *ImageBase;                       // 0x1C sz:0x4
        uint32_t SizeOfNtImage;                // 0x20 sz:0x4
        UNICODE_STRING FullDllName;            // 0x24 sz:0x8
        UNICODE_STRING BaseDllName;            // 0x2C sz:0x8
        uint32_t Flags;                        // 0x34 sz:0x4
        uint32_t SizeOfFullImage;              // 0x38 sz:0x4
        void *EntryPoint;                      // 0x3C sz:0x4
        uint16_t LoadCount;                    // 0x40 sz:0x2
        uint16_t ModuleIndex;                  // 0x42 sz:0x2
        void *DllBaseOriginal;                 // 0x44 sz:0x4
        uint32_t CheckSum;                     // 0x48 sz:0x4
        uint32_t ModuleLoadFlags;              // 0x4C sz:0x4
        uint32_t TimeDateStamp;                // 0x50 sz:0x4
        void *LoadedImports;                   // 0x54 sz:0x4
        void *XexHeaderBase;                   // 0x58 sz:0x4

        union {
            STRING LoadFileName; // 0x5C sz:0x8

            struct
            {
                void *ClosureRoot;     // 0x5C sz:0x4 LDR_DATA_TABLE_ENTRY
                void *TraversalParent; // 0x60 sz:0x4 LDR_DATA_TABLE_ENTRY
            } asEntry;
        } inf;
    }; // size 0x64

    struct XEX_IMPORT_TABLE
    {
        uint32_t TableSize;           // 0x00 sz:0x04
        uint8_t NextImportDigest[20]; // 0x04 sz:0x14
        uint32_t ModuleNumber;        // 0x18 sz:0x04
        uint32_t Version[2];          // 0x1C sz:0x08
        uint8_t Unused;               // 0x24 sz:0x01
        uint8_t ModuleIndex;          // 0x25 sz:0x01
        uint16_t ImportCount;         // 0x26 sz:0x02
        uint32_t ImportStubAddr[1];   // 0x28 sz:0x04
    };                                // size 0x2C

    struct XEX_IMPORT_DESCRIPTOR
    {
        uint32_t Size;          // 0x0 sz:0x4
        uint32_t NameTableSize; // 0x4 sz:0x4
        uint32_t ModuleCount;   // 0x8 sz:0x4
    };                          // size 0x0C

    void *RtlImageXexHeaderField(void *pXexHeaderBase, uint32_t imageField);
}

#define __isync() __emit(0x4C00012C)

#define doSync(addr) \
    __dcbst(0, addr); \
    __sync(); \
    __isync()
