#pragma once

namespace XexUtils
{
namespace Input
{

struct Gamepad : public XINPUT_GAMEPAD
{
    Gamepad();

    // Records the state (when last updated) of the buttons.
    // These remain set as long as the button is pressed.
    uint16_t LastButtons;
    bool LastLeftTrigger;
    bool LastRightTrigger;

    // Records which buttons were pressed this frame - only set on
    // the frame that the button is first pressed.
    uint16_t PressedButtons;
    bool PressedLeftTrigger;
    bool PressedRightTrigger;

    // Thumbstick values converted to range [-1,+1]
    float ThumbLeftX;
    float ThumbLeftY;
    float ThumbRightX;
    float ThumbRightY;
};

Gamepad *GetInput(uint32_t userIndex = 0);

}
}
