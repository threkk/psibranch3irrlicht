/**
 * MessageObject
 * This class is used to wrap messages
 * Supported type of messages:
 *  - Integer	Can be used with enum
 *  - String
 *  - void*		Can hold any type of data, but needs to be casted

 * Another approach was to use an template, but this won't work because
 * its not possible to create one MessageHandler that works with different kind of MessageClients
 */

#pragma once

#include <string>

class __declspec(dllexport) MessageObject
{
public:
	/**
	 * Create a new instance of MessageObject
	 */
	MessageObject(void);

	/**
	 * Create a new instance of MessageObject with an integer message
	 */
	MessageObject(int message);


	/**
	 * Create a new instance of MessageObject with a string message
	 */
	MessageObject(std::string message);

	/**
	 * Create a new instance of MessageObject with an void pointer as message
	 * The void pointer can hold any type of object
	 */
	MessageObject(void* message);

	virtual ~MessageObject(void);
	
	int iMessage;
	std::string sMessage;
	void* vMessage;
};

