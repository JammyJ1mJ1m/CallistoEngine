#pragma once
#include <string>

class Message
{
protected:
	std::string mType;

public:
	Message(std::string type);
	virtual ~Message();

	std::string GetMessageType()		const { return mType; }

};