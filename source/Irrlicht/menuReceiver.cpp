#include "menuReceiver.h"
#include <assert.h>

namespace irr{


void menuReceiver::init(IGUIEnvironment* guienv, int width, int height)
{
	// Here we add the basic GUI elements to display the buttons
	text = guienv->addStaticText(L"Welcome! Please select an option.",rect<s32>((width / 3), (height/ 30) * 5, (width / 3) * 2, (height/ 30) * 6), false);
	text->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);

	guienv->addButton(rect<s32>((width / 3), (height/ 30) * 8, (width / 3) * 2, (height/ 30) * 11), 0, GUI_ID_JOIN_GAME, L"Join Game", L"Joins a game");
	guienv->addButton(rect<s32>((width / 3), (height/ 30) * 12, (width / 3) * 2, (height/ 30) * 15), 0, GUI_ID_HOST_GAME, L"Host Game", L"Hosts a game");
	guienv->addButton(rect<s32>((width / 3), (height/ 30) * 16, (width / 3) * 2, (height/ 30) * 19), 0, GUI_ID_END_GAME, L"End Game", L"Closes the game");

}

//this function initializes the custom buttons they have a fixed height and width for the size of each buttons
void menuReceiver::init_custom(IGUIEnvironment* guienv, int width, int height, int amount_buttons, const wchar_t *name[], const wchar_t *sub_name[]) //, makeButton makebutton)
{
	for(int i = 0; i < amount_buttons; i++)
	{
		//rect<s32> button = (this->*makebutton)(width, height, i);
		
		custom menu = (custom) i;
		guienv->addButton(rect<s32>((width / 3), (height/ 35) * ((i * 5) + 1), (width / 3) * 2, (height/ 35) * ((i * 5) + 5)), 
			0, 
			 menu, 
			name[i], 
			sub_name[i]);
	}
}

//Implementation of the menuSwitchCases.
bool menuReceiver::menuSwitchCases(const SEvent& event, IGUIEnvironment* guienv, JOIN_GAME join_game, HOST_GAME host_game, JOIN_GAME_SECOND join_game_second, END_GAME end_game, PASS_TURN pass_turn, SURRENDER surrender)
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
						(this->*join_game)();

						return true;

					case GUI_ID_JOIN_GAME_SECOND:

						//convert the wchar to char before clearing the guienv and then start whichever function you want in your game
						(this->*join_game_second)();

						return true;

					case GUI_ID_HOST_GAME:

						guienv->clear();
						/*
							After the GUI is cleared the HOST_GAME function is called and you should implement whatevert functions you want to happen here 
							The next step is that the case returns true.
						*/
						(this->*host_game)();

						return true;

					case GUI_ID_END_GAME:

						guienv->clear();	
						/*
							After the GUI is cleared the JOIN_WSDL function is called. 
							Here you need to start the webservice or load any function you want to happen when this button is clicked
						*/
						(this->*end_game)();

						return true;

						case GUI_ID_PASS_TURN:

							
						/*
							pass the turn
						*/
						(this->*pass_turn)();

						return true;

						case GUI_ID_SURRENDER:

							
						/*
							surrender the game
						*/
						(this->*surrender)();

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

bool menuReceiver::menuCustomCases_1(const SEvent& event, IGUIEnvironment* guienv, menu1 menu1)
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
					case MENU1:

						(this->*menu1)(); 

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

bool menuReceiver::menuCustomCases_2(const SEvent& event, IGUIEnvironment* guienv, menu1 menu1, menu2 menu2)
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
					case MENU1:

						(this->*menu1)(); 

						return true;

					case MENU2:
						
						(this->*menu2)(); 

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

bool menuReceiver::menuCustomCases_3(const SEvent& event, IGUIEnvironment* guienv, menu1 menu1, menu2 menu2, menu3 menu3)
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
					case MENU1:

						result = (this->*menu1)(); 

						return result;

					case MENU2:
						
						result = (this->*menu2)(); 

						return result;

					case MENU3:

						result = (this->*menu3)(); 

						return result;

					default:
						break;
					}
					break;

				default:
					break;
			}
	}
}

bool menuReceiver::menuCustomCases_4(const SEvent& event, IGUIEnvironment* guienv, menu1 menu1, menu2 menu2, menu3 menu3, menu4 menu4)
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
					case MENU1:

						result = (this->*menu1)(); 

						return result;

					case MENU2:
						
						result = (this->*menu2)(); 

						return result;

					case MENU3:

						result = (this->*menu3)(); 

						return result;

					case MENU4:

						result = (this->*menu4)(); 

						return result;

					default:
						break;
					}
					break;

				default:
					break;
			}
	}
}

bool menuReceiver::menuCustomCases_5(const SEvent& event, IGUIEnvironment* guienv, menu1 menu1, menu2 menu2, menu3 menu3, menu4 menu4, menu5 menu5)
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
					case MENU1:

						result = (this->*menu1)(); 

						return result;

					case MENU2:
						
						result = (this->*menu2)(); 

						return result;

					case MENU3:

						result = (this->*menu3)(); 

						return result;

					case MENU4:

						result = (this->*menu4)(); 

						return result;

					case MENU5:

						result = (this->*menu5)(); 

						return result;

					default:
						break;
					}
					break;

				default:
					break;
			}
	}
}

bool menuReceiver::menuCustomCases_6(const SEvent& event, IGUIEnvironment* guienv, menu1 menu1, menu2 menu2, menu3 menu3, menu4 menu4, menu5 menu5, menu6 menu6)
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
					case MENU1:

						result = (this->*menu1)(); 

						return result;

					case MENU2:
						
						result = (this->*menu2)(); 

						return result;

					case MENU3:

						result = (this->*menu3)(); 

						return result;

					case MENU4:

						result = (this->*menu4)(); 

						return result;

					case MENU5:

						result = (this->*menu5)(); 

						return result;

					case MENU6:

						result = (this->*menu6)(); 

						return result;

					default:
						break;
					}
					break;

				default:
					break;
			}
	}
}

