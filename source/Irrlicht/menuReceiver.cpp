#include "menuReceiver.h"
#include <assert.h>

namespace irr{


void menuReceiver::init(IGUIEnvironment* guienv, int width, int height)
{
	// Here we add the basic GUI elements to display the buttons
	guienv->addStaticText(L"Welcome! Please select an option.",rect<s32>((width / 3), (height/ 30) * 5, (width / 3) * 2, (height/ 30) * 6), true);
	
	guienv->addButton(rect<s32>((width / 3), (height/ 30) * 8, (width / 3) * 2, (height/ 30) * 11), 0, GUI_ID_JOIN_GAME, L"Join Game", L"Joins a game");
	guienv->addButton(rect<s32>((width / 3), (height/ 30) * 12, (width / 3) * 2, (height/ 30) * 15), 0, GUI_ID_HOST_GAME, L"Host Game", L"Hosts a game");
	guienv->addButton(rect<s32>((width / 3), (height/ 30) * 16, (width / 3) * 2, (height/ 30) * 19), 0, GUI_ID_JOIN_WSDL, L"Quick Match", L"Starts a quick match, opponent will be automatically assigned.");
	guienv->addButton(rect<s32>((width / 3), (height/ 30) * 20, (width / 3) * 2, (height/ 30) * 23), 0, GUI_ID_START_GAME, L"Start Game", L"Start game without network for test");
}

//Implementation of the menuSwitchCases.
bool menuReceiver::menuSwitchCases(const SEvent& event, IGUIEnvironment* guienv)
{

//this is an if statement that checks is the event is a GUI event type and then it will check what the ID is and select it from the switch case
 if (event.EventType == EET_GUI_EVENT)
    {
		//Set the ID
        s32 id = event.GUIEvent.Caller->getID();

		switch(event.GUIEvent.EventType)
        { 
				//This case is chosen if the event type is a button clicked.
				case EGET_BUTTON_CLICKED:
					switch(id)
					{
					case GUI_ID_JOIN_GAME:

						guienv->clear();
						/* display interface to enter ip address. 
						   When implementing the JOIN_GAME function be sure to make a wchar_t pointer where you write something to the player example: Enter IP here
						   Then add a EditBox so the player can enter the text there and add a button that starts the JOIN_GAME_SECOND case.
						*/
						JOIN_GAME();

						return true;

					case GUI_ID_JOIN_GAME_SECOND:

						//convert the wchar to char before clearing the guienv and then start whichever function you want in your game
						JOIN_GAME_SECOND();

						return true;

					case GUI_ID_HOST_GAME:

						guienv->clear();
						/*
							After the GUI is cleared the HOST_GAME function is called and you should implement whatevert functions you want to happen here 
							The next step is that the case returns true.
						*/
						HOST_GAME();

						return true;

					case GUI_ID_JOIN_WSDL:

						guienv->clear();	
						/*
							After the GUI is cleared the JOIN_WSDL function is called. 
							Here you need to start the webservice or load any function you want to happen when this button is clicked
						*/
						JOIN_WSDL();

						return true;

					case GUI_ID_START_GAME:

						guienv->clear();
						/*
							After the GUI is cleared the START_GAME function is called
							Here you should implement any code you want to just load your game. This can be for testing purpose or to just load the singleplayer version of your game.
						*/
						START_GAME();

						return true;

					default:
						break;
					}
					break;

				default:
					break;
				}

		}
	}
}

