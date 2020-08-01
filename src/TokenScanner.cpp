#include "TokenScanner.h"
#include <iostream>
#include <algorithm>

namespace vtf
{

TokenScanner::TokenScanner(IStreamTokenizer& i_streamTokenizer)
{
	i_streamTokenizer.call_onNewToken = std::bind(&TokenScanner::processNewToken,this,std::placeholders::_1);
}
void TokenScanner::register_rule(ScannerRule i_rule)
{
	m_rules.emplace_back(std::move(i_rule));
}
std::string TokenScanner::acquire_resolved_tokens()
{
	return std::move(m_resolvedTokens);
}
void TokenScanner::processNewToken(const token& i_token)
{
	bool acquired = false;

	m_accTokens.emplace_back(i_token);

	if (accept_token(i_token) == false)
	{
		match_degree matchDegree = resolve_token(i_token) - m_accTokens[0].second.m_pos; // local coordinates

		clear_rules();

		if (matchDegree < m_accTokens.size() - 1)
		{
			m_accTokens.erase(m_accTokens.begin(),m_accTokens.begin() + matchDegree + 1);
			resolve_pending_tokens(std::move(m_accTokens));
		}
		else
		{
			m_accTokens.clear();
		}
	}
}
bool TokenScanner::accept_token(const token& i_token)
{
	bool acquired = false;

	std::vector<ScannerRule>::iterator itRule = m_rules.begin();
	for (; itRule != m_rules.end(); ++itRule)
	{
		if (itRule->accept(i_token))
		{
			acquired = true;
		}
	}

	return acquired;
}
match_degree TokenScanner::resolve_token(const token& i_token)
{
	//look for the rule with the highest degree
	std::vector<ScannerRule>::iterator itMaxRule = std::max_element(m_rules.begin(),m_rules.end(),[](const ScannerRule& i_lhs, const ScannerRule& i_rhs){ return i_lhs.get_match_degree() < i_rhs.get_match_degree(); });

	match_degree highestDegree = k_invalidDegree;

	if (itMaxRule != m_rules.end() && itMaxRule->get_match_degree() != k_invalidDegree)
	{
		highestDegree = itMaxRule->get_match_degree();

		m_resolvedTokens += itMaxRule->acquire_match();
	}
	else
	{
		highestDegree = i_token.second.m_pos;

		m_resolvedTokens += i_token.second.m_data;
	}

	return highestDegree;
}
void TokenScanner::clear_rules()
{
	std::vector<ScannerRule>::iterator itRule = m_rules.begin();
	for (; itRule != m_rules.end(); ++itRule)
	{
		itRule->clear();
	}
}
void TokenScanner::resolve_pending_tokens(std::vector<token> i_pensingTokens)
{
	std::vector<token>::iterator itToken = i_pensingTokens.begin();
	for(;itToken!=i_pensingTokens.end();++itToken)
	{
		processNewToken(*itToken);
	}
}

}