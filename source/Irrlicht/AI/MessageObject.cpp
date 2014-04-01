#include "AI\MessageObject.h"

MessageObject::MessageObject(MessageClient* origin) : origin(origin)
{
}

MessageObject::MessageObject(int message, MessageClient* origin) : iMessage(message), sMessage(""), vMessage(NULL), origin(origin)
{
}

MessageObject::MessageObject(std::string message, MessageClient* origin): iMessage(-1), sMessage(message), vMessage(NULL), origin(origin)
{
}

MessageObject::MessageObject(void* message, MessageClient* origin): iMessage(-1), sMessage(""), vMessage(message), origin(origin)
{
}

MessageObject::~MessageObject(void)
{
}