#include "TextToNumberRuleTransformer.h"
#include "TextToNumberScannerDefs.h"
#include <sstream>
#include <cmath>

namespace vtf
{

std::string TextToNumberRuleTransformer::transform(intermediate_representation i_tokens) const
{
	unsigned int resolvedNumber = 0;

	try
	{
		number_intermediate_representation nestedTokens = i_tokens.acquire<number_intermediate_representation>();

		number_intermediate_representation::reverse_iterator itToken = nestedTokens.rbegin();
		for (; itToken != nestedTokens.rend(); ++itToken)
		{
			const NumberPos currNumberPos = itToken->first;
			const NumberMultiplier currMultiplier = itToken->second;

			resolvedNumber += static_cast<unsigned int>(currNumberPos) * static_cast<unsigned int>(pow(10,static_cast<unsigned int>(itToken->second)));
		}
	}
	catch (const bad_intermediate_representation&)
	{
		//wtf
	}

	std::ostringstream ostr;

	ostr << resolvedNumber;

	return ostr.str();
}

}