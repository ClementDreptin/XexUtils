# SMC (System Managment Controller)

Change the power LED behavior (the LED in the middle of the power button):

```C++
void Init()
{
    // Play to boot animation where all 4 LEDs turn on and off then make the power LED blink
    XexUtils::SMC::SetPowerLED(XexUtils::SMC::PowerLED_Blink, true);
}
```

Set the color of the 4 LEDs around the power button (the ones that turn on when controllers are connected):

```C++
void Init()
{
    XexUtils::SMC::SetLEDColors(
        XexUtils::SMC::LEDColor_Off,
        XexUtils::SMC::LEDColor_Red,
        XexUtils::SMC::LEDColor_Green,
        XexUtils::SMC::LEDColor_Orange
    );
}
```

Get the temperature of different hardware components:

```C++
void Init()
{
    float cpuTemperatureInCelsius = XexUtils::SMC::GetCpuTemperature();
    float gpuTemperatureInCelsius = XexUtils::SMC::GetGpuTemperature();
    float ramTemperatureInCelsius = XexUtils::SMC::GetRamTemperature();
    float boardTemperatureInCelsius = XexUtils::SMC::GetBoardTemperature();
}
```
