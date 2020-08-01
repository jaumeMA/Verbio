#include "FreeTextRuleAcceptor.h"

namespace vtf
{

bool FreeTextRuleAcceptor::accept(const token& i_token)
{
	if (i_token.first != TokenType::End)
	{
		m_tokens.add(i_token.second.m_data);

		return true;
	}
	else
	{
		return false;
	}
}
intermediate_representation FreeTextRuleAcceptor::acquire_match()
{
	return std::move(m_tokens);
}
match_degree FreeTextRuleAcceptor::get_match_degree() const
{
	return m_tokens.size();
}

}