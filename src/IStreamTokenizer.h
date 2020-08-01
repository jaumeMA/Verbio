#pragma once

#include "TextFormatterDefs.h"
#include <functional>

namespace vtf
{

class IStreamTokenizer
{
public:
	virtual ~IStreamTokenizer() = default;

	std::function<void(const token&)> call_onNewToken;
};

}