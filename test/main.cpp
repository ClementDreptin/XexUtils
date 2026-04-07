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
void Url();
void ValueOrPtr();

void __cdecl main()
{
    DWORD ethernetStatus = XNetGetEthernetLinkStatus();
    bool isConnectedToTheInternet =
        ethernetStatus & XNET_ETHERNET_LINK_ACTIVE ||
        ethernetStatus & XNET_ETHERNET_LINK_WIRELESS;

    TestRunner::Start();

    Expected();

    Filesystem();

    Formatter();

    General();

    if (isConnectedToTheInternet)
        Http();

    Vec2();

    Vec3();

    Vec4();

    Math();

    Memory();

    Optional();

    if (isConnectedToTheInternet)
        Socket();

    Url();

    ValueOrPtr();

    TestRunner::End();
}
