#pragma once

#include "IStreamTokenizer.h"
#include "ScannerRule.h"

namespace vtf
{

class TokenScanner
{
public:
	TokenScanner(IStreamTokenizer& i_streamTokenizer);

	void register_rule(ScannerRule i_rule);
	std::string acquire_resolved_tokens();

private:
	void processNewToken(const token& i_token);

	bool accept_token(const token& i_token);
	match_degree resolve_token(const token& i_token);
	void clear_rules();
	void resolve_pending_tokens(std::vector<token> i_pensingTokens);

	std::vector<ScannerRule> m_rules;
	std::vector<token> m_accTokens;
	std::string m_resolvedTokens;
};

}