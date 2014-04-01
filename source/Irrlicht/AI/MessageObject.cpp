#include "AI\MessageObject.h"

MessageObject::MessageObject(void)
{
}

MessageObject::MessageObject(int message) : iMessage(message), sMessage(""), vMessage(NULL)
{
}

MessageObject::MessageObject(std::string message): iMessage(-1), sMessage(message), vMessage(NULL)
{
}

MessageObject::MessageObject(void* message): iMessage(-1), sMessage(""), vMessage(message)
{
}

MessageObject::~MessageObject(void)
{
}