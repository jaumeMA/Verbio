#pragma once

#include "ScannerDefs.h"

namespace vtf
{

class IScannerRuleTransformer
{
public:
	virtual ~IScannerRuleTransformer() = default;

	virtual std::string transform(intermediate_representation) const = 0;
};

}