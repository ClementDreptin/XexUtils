# Input

The purpose of this class is to provide a more convenient way to detect single button presses and repeats than by just using `XInputGetState`.

Consider the following code:
```C++
// Imagine this function is called every frame
void Update()
{
    // Get the gamepad state
    XINPUT_STATE state = { 0 };
    XInputGetState(0, &state);

    if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
    {
        // Do something when DPAD RIGHT is pressed
    }
}
```
Code inside the `if` block will execute every frame where DPAD RIGHT is pressed and not just once.

When using the `Input` class like this:
```C++
// Imagine this function is called every frame
void Update()
{
    // Get the gamepad state
    Input::Gamepad *pGamepad = Input::GetInput();

    if (pGamepad->PressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
    {
        // Do something when DPAD RIGHT is pressed
    }
}
```
Code inside the `if` block will execute only the first frame where DPAD RIGHT is pressed, and not every frame.

**NOTE**: `Input::Gamepad::PressedButtons` is set again when repeat events are reported by `XInputGetKeystroke`. This means that holding a button will be detected as a normal button press for approximately one second, then button repeats for as long as the button is held.
