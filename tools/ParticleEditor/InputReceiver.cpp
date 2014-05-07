#include "InputReceiver.h"

InputReceiver::InputReceiver(void)
{
	// Create a bool array with all keys
	for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
		KeyIsDown[i] = false;

	mouseWheel = 0;
	deltaMouse = core::position2di(0, 0);
}

bool InputReceiver::OnEvent(const SEvent& event)
{
	// Remember whether each key is down or up
	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
	{
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}

	if(event.EventType == EET_MOUSE_INPUT_EVENT)
    {
		// On scroll
		if (event.MouseInput.Event == EMIE_MOUSE_WHEEL)
		{
			mouseWheel += event.MouseInput.Wheel;
		}
		else
		{
			// Mouse changed position
			deltaMouse = mouse - core::position2di(event.MouseInput.X, event.MouseInput.Y);

			// If the delta mouse is too big, ignore it, probably a mistake
			if (deltaMouse.X > 20 || deltaMouse.X < -20) {
				deltaMouse = core::position2di(0, 0);
			}

			// Save the mouse position
			mouse = core::position2di(event.MouseInput.X, event.MouseInput.Y);
		}
    }

	return false;
}

void InputReceiver::reset(void)
{
	// Reset the delta mouse every frame, so that we dont use the same value the next frame
	deltaMouse = core::position2di(0, 0);
}

bool InputReceiver::IsKeyDown(EKEY_CODE keyCode) const
{
	// Return if the given key is down
	return KeyIsDown[keyCode];
}

InputReceiver::~InputReceiver(void)
{	
}
