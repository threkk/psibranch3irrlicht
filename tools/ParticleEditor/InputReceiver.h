#ifndef INPUTRECEIVER_H
#define INPUTRECEIVER_H

#include <irrlicht.h>

using namespace irr;

class InputReceiver : public IEventReceiver
{
public:
	InputReceiver(void);

	// Movement of the mouse on this frame
	core::position2di deltaMouse;

	// Position of the mouse
	core::position2di mouse; 
	
	// Called by Irrlicht when a key event happens
	virtual bool OnEvent(const SEvent& event);

	// To check if a key is down
	virtual bool IsKeyDown(EKEY_CODE keyCode) const;

	// Reset the input receiver every frame
	void reset(void);

	// How much there is scrolled
	float mouseWheel;

	~InputReceiver(void);
private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

#endif
