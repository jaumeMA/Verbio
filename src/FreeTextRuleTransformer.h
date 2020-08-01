#pragma once

#include "IScannerRuleTransformer.h"

namespace vtf
{

class FreeTextRuleTransfomer : public IScannerRuleTransformer
{
public:
	FreeTextRuleTransfomer() = default;

private:
	std::string transform(intermediate_representation) const override;

};

}