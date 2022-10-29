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

// Static class with functions to interact with the System Management Controller of the Xbox 360.
class SMC
{
public:
    // Set the behavior of the power LED (the one in the middle of the power button).
    static void SetPowerLED(PowerLEDMode mode, bool animate);

    // Set the color of the 4 LEDs around the power button (the ones that turn on when controllers are connected).
    static void SetLEDColors(LEDColor topLeft, LEDColor topRight, LEDColor bottomLeft, LEDColor bottomRight);

private:
    static uint8_t s_CommandBuffer[16];
};

}
