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
		GUI_ID_JOIN_WSDL,
		GUI_ID_START_GAME
	};

	using namespace core;
	using namespace scene;
	using namespace video;
	using namespace io;
	using namespace gui; 

	class IRRLICHT_API menuReceiver : public IEventReceiver
	{
		public: 
			//This init function loads the buttons on the screen. It needs the width and height of the device and also the GUIenvironment.
			void init(IGUIEnvironment* guienv, int width, int height);

			//This is a bool function which has cases for the different GUI ID's that can be selected.
			bool menuSwitchCases(const SEvent& event, IGUIEnvironment* guienv);

			//Function that need to be implemented when you use this interface so that the buttons do something.
			virtual void JOIN_GAME(void){};
			virtual void HOST_GAME(void){};
			virtual void JOIN_GAME_SECOND(void){};
			virtual void JOIN_WSDL(void){};
			virtual void START_GAME(void){};
			
			//Standard OnEvent method that needs to be implemented.
			virtual bool OnEvent(const SEvent& event) = 0;

	};

}



#endif