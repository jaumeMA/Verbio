#pragma once

#include "IScannerRuleAcceptor.h"

namespace vtf
{

class FreeTextRuleAcceptor : public IScannerRuleAcceptor
{
public:
	FreeTextRuleAcceptor() = default;

private:
	bool accept(const token&) override;
	intermediate_representation acquire_match() override;
	match_degree get_match_degree() const override;

	default_intermdiate_representation m_tokens;
};

}