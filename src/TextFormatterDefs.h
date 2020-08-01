#pragma once

#include <cstdint>
#include <utility>
#include <string>

namespace vtf
{

enum class TokenType : uint8_t
{
	None,
	Text,
	Number,
	AlphaNumeric,
	Space,
	Symbol,
	End
};

struct token_t
{
	size_t m_pos = 0;
	std::string m_data;
};

typedef std::pair<TokenType,token_t> token;

}