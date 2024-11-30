#pragma once
#include <string>

class Message
{
protected:
	std::string mType;

	Message(std::string type);
	virtual ~Message();

public:
	std::string GetMessageType()		const { return mType; }

};