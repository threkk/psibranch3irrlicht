/*
* This is a base interface for the menu receiver that can be used.
* Instead of implementing the normal IEventReceiver this interface can be used.
* It holds everything for a standard menu with some predefined options and new options can be added later.
*/
#ifndef MENU_RECEIVER_H
#define MENU_RECEIVER_H

#include "../../include/IrrCompileConfig.h"

#include "IEventReceiver.h"
#include "IGUIEnvironment.h"
#include "irrlicht.h"



namespace irr
{
	//An enum which holds the types of GUI ID's that are made for the standard menu.
	enum
	{
		GUI_ID_JOIN_GAME,
		GUI_ID_HOST_GAME,
		GUI_ID_JOIN_GAME_SECOND,
		GUI_ID_END_GAME
		
	};

	//An enum which holds the types of GUI ID's for the custom menu.
	enum custom
	{
		MENU1,
		MENU2,
		MENU3,
		MENU4,
		MENU5,
		MENU6
	};

	using namespace core;
	using namespace scene;
	using namespace video;
	using namespace io;
	using namespace gui; 

	class IRRLICHT_API menuReceiver : public IEventReceiver
	{
		public: 
			//This init function loads the buttons on the screen. It needs the width and height of the device and also the GUIEnvironment.
			void init(IGUIEnvironment* guienv, int width, int height);
			
			//This init function loads the amount of buttons you want. It needs the width and height of the device and also the GUIEnvironment and also the number of buttons.
			void init_custom(IGUIEnvironment* guienv, int width, int height, int amount_buttons, const wchar_t *name[], const wchar_t *sub_name[]);

			//typedef of the function pointers you need if you're using the networking menu.
			typedef bool (menuReceiver::*JOIN_GAME)(void);
			typedef bool (menuReceiver::*HOST_GAME)(void);
			typedef bool (menuReceiver::*JOIN_GAME_SECOND)(void);
			typedef bool (menuReceiver::*END_GAME)(void);

			//typedef of the funtion pointers for custom buttons.
			typedef bool (menuReceiver::*menu1)(void);
			typedef bool (menuReceiver::*menu2)(void);
			typedef bool (menuReceiver::*menu3)(void);
			typedef bool (menuReceiver::*menu4)(void);
			typedef bool (menuReceiver::*menu5)(void);
			typedef bool (menuReceiver::*menu6)(void);

			//This is a bool function which has cases for the different GUI ID's that can be selected. It is used for the menu
			bool menuSwitchCases(const SEvent& event, IGUIEnvironment* guienv, JOIN_GAME join_game, HOST_GAME host_game, JOIN_GAME_SECOND join_game_second, END_GAME end_game);

			//The is the bool functions for the buttons depending on how many buttons you make you need to add the functions to this functions
			bool menuCustomCases_1(const SEvent& event, IGUIEnvironment* guienv, menu1 menu1);
			bool menuCustomCases_2(const SEvent& event, IGUIEnvironment* guienv, menu1 menu1, menu2 menu2);
			bool menuCustomCases_3(const SEvent& event, IGUIEnvironment* guienv, menu1 menu1, menu2 menu2, menu3 menu3);
			bool menuCustomCases_4(const SEvent& event, IGUIEnvironment* guienv, menu1 menu1, menu2 menu2, menu3 menu3, menu4 menu4);
			bool menuCustomCases_5(const SEvent& event, IGUIEnvironment* guienv, menu1 menu1, menu2 menu2, menu3 menu3, menu4 menu4, menu5 menu5);
			bool menuCustomCases_6(const SEvent& event, IGUIEnvironment* guienv, menu1 menu1, menu2 menu2, menu3 menu3, menu4 menu4, menu5 menu5, menu6 menu6);

			
			//Standard OnEvent method that needs to be implemented.
			virtual bool OnEvent(const SEvent& event) = 0;

			IGUIStaticText *text;

			custom menu_ID[5];

			bool result;

	};

}



#endif