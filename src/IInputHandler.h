#pragma once

#include <functional>
#include "TextFormatterDefs.h"
#include <istream>

namespace vtf
{

class IInputHandler
{
public:
	std::function<void(std::istream&)> call_onNewStream;

	virtual ~IInputHandler() = default;
	virtual void start() = 0;
	virtual void stop() = 0;
};

}