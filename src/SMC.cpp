#include "pch.h"
#include "SMC.h"

// Imports from xboxkrnl.exe
extern "C"
{
    void HalSendSMCMessage(void *pInput, void *pOutput);
}

namespace XexUtils
{

uint8_t SMC::s_CommandBuffer[16] = { 0 };

void SMC::SetPowerLED(PowerLEDMode mode, bool animate)
{
    ZeroMemory(s_CommandBuffer, sizeof(s_CommandBuffer));

    s_CommandBuffer[0] = 0x8C;
    s_CommandBuffer[1] = static_cast<uint8_t>(mode);
    s_CommandBuffer[2] = (animate ? 0x01 : 0x00);

    HalSendSMCMessage(s_CommandBuffer, nullptr);
}

void SMC::SetLEDColors(LEDColor topLeft, LEDColor topRight, LEDColor bottomLeft, LEDColor bottomRight)
{
    ZeroMemory(s_CommandBuffer, sizeof(s_CommandBuffer));

    s_CommandBuffer[0] = 0x99;
    s_CommandBuffer[1] = 0x01;

    s_CommandBuffer[2] = static_cast<uint8_t>(topLeft) >> 3 |
                         static_cast<uint8_t>(topRight) >> 2 |
                         static_cast<uint8_t>(bottomLeft) >> 1 |
                         static_cast<uint8_t>(bottomRight);

    HalSendSMCMessage(s_CommandBuffer, nullptr);
}

}
