#pragma once

#include <functional>

namespace vtf
{

class ITextFormatter
{
public:
	virtual ~ITextFormatter() = default;

	std::function<void(const std::string&)> call_onNewTextFormatted;

};

}