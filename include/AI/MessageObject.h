#pragma once

#include <string>
class MessageClient; // Instead of including

/**
 * MessageObject
 * This class is used to wrap messages
 * Supported type of messages:
 *  - Integer
 *  - String
 *  - void*		Can hold any type of data, but needs to be casted
 *
 * Another approach was to use templates, but this won't work because
 * its not possible to create only one MessageHandler that works with different kind of MessageClients/MessageObjects
 */
class __declspec(dllexport) MessageObject
{
public:
	/**
	 * Create a new instance of MessageObject
	 */
	MessageObject(MessageClient* origin);

	/**
	 * Create a new instance of MessageObject with an integer message
	 */
	MessageObject(int message, MessageClient* origin);


	/**
	 * Create a new instance of MessageObject with a string message
	 */
	MessageObject(std::string message, MessageClient* origin);

	/**
	 * Create a new instance of MessageObject with an void pointer as message
	 * The void pointer can hold any type of object
	 */
	MessageObject(void* message, MessageClient* origin);

	virtual ~MessageObject(void);
	
	// Contains an integer message
	int iMessage;

	// Contains a string message
	std::string sMessage;
	
	// Contains a void* message
	void* vMessage;

	// Contains the topic of the message. No need to set manually, because it will be set by the MessageHandler
	std::string topic;

	// Contains the origin of the message
	MessageClient* origin;
};