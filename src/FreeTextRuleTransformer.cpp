#include "FreeTextRuleTransformer.h"

namespace vtf
{

std::string FreeTextRuleTransfomer::transform(intermediate_representation i_tokens) const
{
	std::string res;
	try
	{
		default_intermdiate_representation nestedTokens = i_tokens.acquire<default_intermdiate_representation>();
		default_intermdiate_representation::const_iterator itToken = nestedTokens.begin();
		for (; itToken != nestedTokens.end(); ++itToken)
		{
			res += *itToken;
		}
	}
	catch (const bad_intermediate_representation&)
	{
		//wtf
	}

	return res;
}

}