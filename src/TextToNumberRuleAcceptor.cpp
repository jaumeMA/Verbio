#include "TextToNumberRuleAcceptor.h"
#include <algorithm>
#include <cctype>

namespace vtf
{

std::map<std::string, NumberPos> initializeNumberMap()
{
	std::map<std::string, NumberPos> res;

	//units
	res["zero"] = NumberPos::Zero;
	res["one"] = NumberPos::One;
	res["two"] = NumberPos::Two;
	res["three"] = NumberPos::Three;
	res["four"] = NumberPos::Four;
	res["five"] = NumberPos::Five;
	res["six"] = NumberPos::Six;
	res["seven"] = NumberPos::Seven;
	res["eight"] = NumberPos::Eight;
	res["nine"] = NumberPos::Nine;

	//tens
	res["ten"] = NumberPos::Ten;
	res["eleven"] = NumberPos::Eleven;
	res["twelve"] = NumberPos::Twelve;
	res["thirteen"] = NumberPos::Thirteen;
	res["fourteen"] = NumberPos::Fourteen;
	res["fifteen"] = NumberPos::Fifteen;
	res["sixteen"] = NumberPos::Sixteen;
	res["seventeen"] = NumberPos::Seventeen;
	res["eighteen"] = NumberPos::Eighteen;
	res["twenty"] = NumberPos::Twenty;
	res["thirty"] = NumberPos::Thirty;
	res["fourty"] = NumberPos::Fourty;
	res["fifty"] = NumberPos::Fifty;
	res["sixty"] = NumberPos::Sixty;
	res["seventy"] = NumberPos::Seventy;
	res["eighty"] = NumberPos::Eighty;
	res["ninety"] = NumberPos::Ninety;

	return res;
}
std::map<std::string, NumberMultiplier> initializeMultiplerMap()
{
	std::map<std::string, NumberMultiplier> res;

	res["hundred"] = NumberMultiplier::Hundred;
	res["thousand"] = NumberMultiplier::Thousand;
	res["million"] = NumberMultiplier::Million;
	res["billion"] = NumberMultiplier::Billion;

	return res;
}

std::map<std::string,NumberPos> TextToNumberRuleAcceptor::s_numberMap = initializeNumberMap();
std::map<std::string,NumberMultiplier> TextToNumberRuleAcceptor::s_MultiplierMap = initializeMultiplerMap();

NumberPlace fromNumberPosToNumberPlace(NumberPos i_number)
{
	if (i_number >=NumberPos::Zero && i_number < NumberPos::Ten)
	{
		return NumberPlace::Units;
	}
	else
	{
		return NumberPlace::Tens;
	}
}
NumberPlace fromNumberMultiplierToNumberPlace(NumberMultiplier i_number)
{
	switch (i_number)
	{
		case NumberMultiplier::Hundred:
			return NumberPlace::Hundreds;
		case NumberMultiplier::Thousand:
			return NumberPlace::Thousands;
		case NumberMultiplier::Million:
			return NumberPlace::Millions;
		case NumberMultiplier::Billion:
			return NumberPlace::Billions;
		default:
			return NumberPlace::None;
	}
}

bool TextToNumberRuleAcceptor::accept(const token& i_token)
{
	if (m_acceptingTokens == false)
	{
		return m_acceptingTokens;
	}
	else
	{
		//recheck acceptance
		m_acceptingTokens = false;

		std::string token = i_token.second.m_data;
		std::transform(token.begin(), token.end(), token.begin(),[](unsigned char c){ return std::tolower(c); });

		std::pair<NumberPlace,unsigned int> currTokenPlacePair = get_place(i_token.first,token);

		switch (currTokenPlacePair.first)
		{
			case NumberPlace::None:
			{
				if (token == " " && m_state != NumberPlace::None)
				{
					m_acceptingTokens = true;
				}
				else if (token == "-" && m_state == NumberPlace::Tens)
				{
					m_acceptingTokens = true;
				}
				else if (token == "and" && m_state == NumberPlace::Hundreds)
				{
					m_acceptingTokens = true;
				}

				break;
			}
			case NumberPlace::Units:
			{
				if (m_state != NumberPlace::Units)
				{
					m_state = NumberPlace::Units;
					m_resolvedTokens.add(static_cast<NumberPos>(currTokenPlacePair.second));
					m_lastAcceptedToken = i_token.second.m_pos;
					m_acceptingTokens = true;
				}

				break;
			}
			case NumberPlace::Tens:
			{
				if (m_state == NumberPlace::Units || m_state == NumberPlace::Tens)
				{ // this is for dates
					if (m_resolvedTokens.size() == 1)
					{
						m_state = NumberPlace::Tens;
						m_resolvedTokens.set_multiplier(NumberMultiplier::Hundred);
						m_resolvedTokens.add(static_cast<NumberPos>(currTokenPlacePair.second));
						m_lastAcceptedToken = i_token.second.m_pos;
						m_acceptingTokens = true;
					}
				}
				else
				{
					m_state = NumberPlace::Tens;
					m_resolvedTokens.add(static_cast<NumberPos>(currTokenPlacePair.second));
					m_lastAcceptedToken = i_token.second.m_pos;
					m_acceptingTokens = true;
				}

				break;
			}
			default:
			{
				if (m_state == NumberPlace::None)
				{
					m_state = currTokenPlacePair.first;
					m_resolvedTokens.add(NumberPos::One);
					m_resolvedTokens.set_multiplier(static_cast<NumberMultiplier>(currTokenPlacePair.second));
					m_lastAcceptedToken = i_token.second.m_pos;
					m_acceptingTokens = true;
				}
				else if (m_state == NumberPlace::Units || m_state == NumberPlace::Tens)
				{
					m_state = currTokenPlacePair.first;
					m_resolvedTokens.set_multiplier(static_cast<NumberMultiplier>(currTokenPlacePair.second));
					m_lastAcceptedToken = i_token.second.m_pos;
					m_acceptingTokens = true;
				}
			}
		}
	}

	return m_acceptingTokens;
}
void TextToNumberRuleAcceptor::clear()
{
	m_state = NumberPlace::None;
	m_acceptingTokens = true;
	m_lastAcceptedToken = k_invalidDegree;
	m_resolvedTokens.clear();
}
intermediate_representation TextToNumberRuleAcceptor::acquire_match()
{
	return m_resolvedTokens;
}
match_degree TextToNumberRuleAcceptor::get_match_degree() const
{
	return m_lastAcceptedToken;
}
std::pair<NumberPlace,unsigned int> TextToNumberRuleAcceptor::get_place(TokenType i_type, const std::string& i_token) const
{
	if (i_type == TokenType::Number)
	{
		int nestedNumber = atoi(i_token.c_str());

		if (nestedNumber >= 0 && nestedNumber < 100)
		{
			return std::make_pair(NumberPlace::Units,nestedNumber);
		}
	}
	else
	{
		std::map<std::string,NumberPos>::const_iterator itNumber = s_numberMap.find(i_token);
		if (itNumber != s_numberMap.end())
		{
			return std::make_pair(fromNumberPosToNumberPlace(itNumber->second),static_cast<unsigned int>(itNumber->second));
		}

		std::map<std::string,NumberMultiplier>::const_iterator itMultiplier = s_MultiplierMap.find(i_token);
		if (itMultiplier != s_MultiplierMap.end())
		{
			return std::make_pair(fromNumberMultiplierToNumberPlace(itMultiplier->second),static_cast<unsigned int>(itMultiplier->second));
		}
	}

	return std::make_pair(NumberPlace::None,0);
}

}