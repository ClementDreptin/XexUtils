#pragma once

namespace XexUtils
{

typedef enum _LEDColor
{
    LEDColor_Off = 0x00,
    LEDColor_Red = 0x08,
    LEDColor_Green = 0x80,
    LEDColor_Orange = 0x88,
} LEDColor;

typedef enum _PowerLEDMode
{
    PowerLED_On = 0x01,
    PowerLED_Default = 0x02,
    PowerLED_Off = 0x03,
    PowerLED_Blink = 0x10,
} PowerLEDMode;

class SMC
{
public:
    static void SetPowerLED(PowerLEDMode mode, bool animate);

    static void SetLEDColors(LEDColor topLeft, LEDColor topRight, LEDColor bottomLeft, LEDColor bottomRight);

private:
    static uint8_t s_CommandBuffer[16];
};

}
