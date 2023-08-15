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
}

#define __isync() __emit(0x4C00012C)

#define doSync(addr) \
    while (0) \
    { \
        __dcbst(0, addr); \
        __sync(); \
        __isync(); \
    }
