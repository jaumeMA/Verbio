#include "TextToNumberScannerDefs.h"

namespace vtf
{

void number_intermediate_representation::add(NumberPos i_number)
{
	return m_tokens.push_back({i_number,NumberMultiplier::None});
}
void number_intermediate_representation::set_multiplier(NumberMultiplier i_multiplier)
{
	if (m_tokens.empty() == false)
	{
		m_tokens[m_tokens.size() - 1].second = i_multiplier;
	}
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