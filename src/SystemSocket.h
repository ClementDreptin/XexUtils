#pragma once

/// @file SystemSocket.h
///
/// Macros to override the standard socket functions with their internal version and run
/// them with the proper process type, either title of system (`XNCALLER_TITLE` or
/// `XNCALLER_SYSAPP` respectively).

#include "Kernel.h"

#define closesocket(s) NetDll_closesocket((XNCALLER_TYPE)KeGetCurrentProcessType(), s)
#define connect(s, name, namelen) NetDll_connect((XNCALLER_TYPE)KeGetCurrentProcessType(), s, name, namelen)
#define inet_addr(cp) NetDll_inet_addr(cp)
#define recv(s, buf, len, flags) NetDll_recv((XNCALLER_TYPE)KeGetCurrentProcessType(), s, buf, len, flags)
#define send(s, buf, len, flags) NetDll_send((XNCALLER_TYPE)KeGetCurrentProcessType(), s, buf, len, flags)
#define setsockopt(s, level, optname, optval, optlen) NetDll_setsockopt((XNCALLER_TYPE)KeGetCurrentProcessType(), s, level, optname, optval, optlen)
#define shutdown(s, how) NetDll_shutdown((XNCALLER_TYPE)KeGetCurrentProcessType(), s, how)
#define socket(af, type, protocol) NetDll_socket((XNCALLER_TYPE)KeGetCurrentProcessType(), af, type, protocol)
#define WSACleanup() NetDll_WSACleanup((XNCALLER_TYPE)KeGetCurrentProcessType())
#define WSAStartup(wVersionRequested, lpWSAData) NetDll_WSAStartupEx((XNCALLER_TYPE)KeGetCurrentProcessType(), wVersionRequested, lpWSAData, 2)
#define XNetCleanup() NetDll_XNetCleanup((XNCALLER_TYPE)KeGetCurrentProcessType())
#define XNetDnsLookup(pszHost, hEvent, ppxndns) NetDll_XNetDnsLookup((XNCALLER_TYPE)KeGetCurrentProcessType(), pszHost, hEvent, ppxndns)
#define XNetDnsRelease(pxndns) NetDll_XNetDnsRelease((XNCALLER_TYPE)KeGetCurrentProcessType(), pxndns)
#define XNetStartup(pxnsp) NetDll_XNetStartup((XNCALLER_TYPE)KeGetCurrentProcessType(), pxnsp)
