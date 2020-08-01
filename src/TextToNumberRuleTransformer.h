#pragma once

#include "IScannerRuleTransformer.h"
#include <map>

namespace vtf
{

class TextToNumberRuleTransformer : public IScannerRuleTransformer
{
public:
	TextToNumberRuleTransformer() = default;

private:
	std::string transform(intermediate_representation i_tokens) const override;

	static std::map<std::string,unsigned int> m_textToNumber;
};

}