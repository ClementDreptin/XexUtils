#include <xtl.h>

#include "TestRunner.h"

void Expected();
void Filesystem();
void Formatter();
void General();
void Http();
void Vec2();
void Vec3();
void Vec4();
void Math();
void Memory();
void Optional();
void Socket();
void ValueOrPtr();

void __cdecl main()
{
    TestRunner::Start();

    Expected();

    Filesystem();

    Formatter();

    General();

    Http();

    Vec2();

    Vec3();

    Vec4();

    Math();

    Memory();

    Optional();

    // Only run socket tests when connected to the internet
    DWORD ethernetStatus = XNetGetEthernetLinkStatus();
    if (ethernetStatus & XNET_ETHERNET_LINK_ACTIVE || ethernetStatus & XNET_ETHERNET_LINK_WIRELESS)
        Socket();

    ValueOrPtr();

    TestRunner::End();
}
