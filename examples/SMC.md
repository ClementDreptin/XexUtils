# System Managment Controller (SMC)

Change the power LED behavior (the LED in the middle of the power button):

```C++
void Init()
{
    // Play to boot animation where all 4 LEDs turn on and off then make the power LED blink
    XexUtils::SMC::SetPowerLED(SMC::PowerLED_Blink, true);
}
```

Set the color of the 4 LEDs around the power button (the ones that turn on when controllers are connected):

```C++
void Init()
{
    XexUtils::SMC::SetLEDColors(SMC::LEDColor_Off, SMC::LEDColor_Red, SMC::LEDColor_Green, SMC::LEDColor_Orange);
}
```
