#pragma once

#include "ScannerDefs.h"
#include "TextFormatterDefs.h"

namespace vtf
{

class IScannerRuleAcceptor
{
public:
	virtual ~IScannerRuleAcceptor() = default;

	virtual bool accept(const token&) = 0;
	virtual intermediate_representation acquire_match() = 0;
	virtual void clear() = 0;
	virtual match_degree get_match_degree() const = 0;
};

}