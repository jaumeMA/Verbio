#include "TextToNumberScannerDefs.h"

namespace vtf
{

number_intermediate_representation::number_intermediate_representation(unsigned int i_maxMultiplier)
: m_maxMultiplier(i_maxMultiplier)
{
}
void number_intermediate_representation::add(NumberPos i_number)
{
	return m_tokens.push_back({i_number,NumberMultiplier::None});
}
bool number_intermediate_representation::try_set_multiplier(NumberMultiplier i_multiplier)
{
	//checkin stage
	unsigned int prevMultiplier = 0;
	std::vector<std::pair<NumberPos,NumberMultiplier>>::reverse_iterator itTokenCheck = m_tokens.rbegin();
	for (; itTokenCheck != m_tokens.rend(); ++itTokenCheck)
	{
		if (itTokenCheck->second < i_multiplier)
		{
			prevMultiplier = static_cast<unsigned int>(itTokenCheck->second) + static_cast<unsigned int>(i_multiplier);
		}
		else if(prevMultiplier >= static_cast<unsigned int>(itTokenCheck->second))
		{
			return false;
		}
		else
		{
			break;
		}
	}

	//apply max multiplier rule
	if (prevMultiplier > m_maxMultiplier)
	{
		return false;
	}

	//apply stage
	std::vector<std::pair<NumberPos,NumberMultiplier>>::reverse_iterator itTokenApply = m_tokens.rbegin();
	for (; itTokenApply != m_tokens.rend(); ++itTokenApply)
	{
		if (itTokenApply->second < i_multiplier)
		{
			itTokenApply->second = static_cast<NumberMultiplier>(static_cast<unsigned int>(itTokenApply->second) + static_cast<unsigned int>(i_multiplier));
		}
		else
		{
			break;
		}
	}

	return true;
}
bool number_intermediate_representation::empty() const
{
	return m_tokens.empty();
}
size_t number_intermediate_representation::size() const
{
	return m_tokens.size();
}
void number_intermediate_representation::clear()
{
	m_tokens.clear();
}
number_intermediate_representation::iterator number_intermediate_representation::begin()
{
	return m_tokens.begin();
}
number_intermediate_representation::iterator number_intermediate_representation::end()
{
	return m_tokens.end();
}
number_intermediate_representation::reverse_iterator number_intermediate_representation::rbegin()
{
	return m_tokens.rbegin();
}
number_intermediate_representation::reverse_iterator number_intermediate_representation::rend()
{
	return m_tokens.rend();
}
number_intermediate_representation::const_iterator number_intermediate_representation::begin() const
{
	return m_tokens.begin();
}
number_intermediate_representation::const_iterator number_intermediate_representation::end() const
{
	return m_tokens.end();
}
number_intermediate_representation::const_reverse_iterator number_intermediate_representation::rbegin() const
{
	return m_tokens.rbegin();
}
number_intermediate_representation::const_reverse_iterator number_intermediate_representation::rend() const
{
	return m_tokens.rend();
}

}