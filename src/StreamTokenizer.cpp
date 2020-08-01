#include "StreamTokenizer.h"
#include <regex>

namespace vtf
{

const std::regex k_symbolRule("[^0-9a-zA-Z]");
const std::regex k_numberRule("[0-9]");
const std::regex k_letterRule("[a-zA-Z]");

void StreamTokenizer::token_data::add_data(TokenType i_type, char i_data)
{
	if (m_type == TokenType::None)
	{
		m_type = i_type;
	}
	else if (m_type != i_type)
	{
		m_type = TokenType::AlphaNumeric;
	}
	else
	{
		m_type = i_type;
	}

	m_data += i_data;
}
void StreamTokenizer::token_data::clear()
{
	m_type = TokenType::None;
	m_data.clear();
}
bool StreamTokenizer::token_data::empty() const
{
	return (m_type == TokenType::None) && m_data.empty();
}
token StreamTokenizer::token_data::get(size_t i_tokenCounter) const
{
	token_t newToken = { i_tokenCounter, m_data};

	return token(m_type,newToken);
}

void StreamTokenizer::processStream(std::istream& i_stream)
{
	char currChar = 0;

	while (i_stream.get(currChar))
	{
		const std::string currStr(1,currChar);

		if (std::regex_match(currStr.c_str(), k_symbolRule))
		{
			if (m_currToken.empty() == false)
			{
				call_onNewToken(m_currToken.get(m_tokenCounter));
				m_tokenCounter++;
				m_currToken.clear();
			}

			call_onNewToken(token(TokenType::Symbol,{m_tokenCounter,currStr}));
			m_tokenCounter++;
		}
		else if (std::regex_match(currStr.c_str(), k_numberRule))
		{
			m_currToken.add_data(TokenType::Number,currChar);
		}
		else if (std::regex_match(currStr.c_str(), k_letterRule))
		{
			m_currToken.add_data(TokenType::Text,currChar);
		}
	}

	if (m_currToken.empty() == false)
	{
		call_onNewToken(m_currToken.get(m_tokenCounter));
		m_tokenCounter++;
		m_currToken.clear();
	}

	call_onNewToken(token(TokenType::End,{m_tokenCounter,""}));
}

}