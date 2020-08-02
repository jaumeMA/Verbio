#pragma once

#include "IScannerRuleAcceptor.h"
#include "TextToNumberScannerDefs.h"
#include <map>

namespace vtf
{

enum class NumberPlace : uint8_t
{
	None,
	Units,
	Tens,
	Hundreds,
	Thousands,
	Millions,
	Billions
};


class TextToNumberRuleAcceptor : public IScannerRuleAcceptor
{
public:
	TextToNumberRuleAcceptor(unsigned int i_maxMultiplier);

private:
	bool accept(const token&) override;
	void clear() override;
	intermediate_representation acquire_match() override;
	match_degree get_match_degree() const override;

	std::pair<NumberPlace,unsigned int> get_place(TokenType i_type, const std::string& i_token) const;

	NumberPlace m_state = NumberPlace::None;
	number_intermediate_representation m_resolvedTokens;
	size_t m_lastAcceptedToken = k_invalidDegree;
	bool m_acceptingTokens = true;

	static std::map<std::string,NumberPos> s_numberMap;
	static std::map<std::string,NumberMultiplier> s_MultiplierMap;
};

}