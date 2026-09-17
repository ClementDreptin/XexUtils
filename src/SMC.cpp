#include <cstdint>

#include "Kernel.h"
#include "SMC.h"

namespace XexUtils
{
namespace SMC
{

#define BUFFER_SIZE 16

void SetPowerLED(PowerLEDMode mode, bool animate)
{
    uint8_t input[BUFFER_SIZE] = {};

    input[0] = 0x8C;
    input[1] = static_cast<uint8_t>(mode);
    input[2] = (animate ? 0x01 : 0x00);

    HalSendSMCMessage(input, nullptr);
}

void SetLEDColors(LEDColor topLeft, LEDColor topRight, LEDColor bottomLeft, LEDColor bottomRight)
{
    uint8_t input[BUFFER_SIZE] = {};

    input[0] = 0x99;
    input[1] = 0x01;

    input[2] = static_cast<uint8_t>(topLeft) >> 3 |
               static_cast<uint8_t>(topRight) >> 2 |
               static_cast<uint8_t>(bottomLeft) >> 1 |
               static_cast<uint8_t>(bottomRight);

    HalSendSMCMessage(input, nullptr);
}

typedef enum _TemperatureComponentIndex
{
    TemperatureComponentIndex_Cpu,
    TemperatureComponentIndex_Gpu = 2,
    TemperatureComponentIndex_Ram = 4,
    TemperatureComponentIndex_Board = 6,
} TemperatureComponentIndex;

static float GetTemperature(TemperatureComponentIndex index)
{
    uint8_t input[BUFFER_SIZE] = {};
    uint8_t output[BUFFER_SIZE] = {};

    input[0] = 0x07;
    HalSendSMCMessage(input, output);

    return static_cast<float>(
               static_cast<uint32_t>(output[index + 2]) << 8 |
               static_cast<uint32_t>(output[index + 1])
           ) /
           256.0f;
}

float GetCpuTemperature()
{
    return GetTemperature(TemperatureComponentIndex_Cpu);
}

float GetGpuTemperature()
{
    return GetTemperature(TemperatureComponentIndex_Gpu);
}

float GetRamTemperature()
{
    return GetTemperature(TemperatureComponentIndex_Ram);
}

float GetBoardTemperature()
{
    return GetTemperature(TemperatureComponentIndex_Board);
}

}
}
