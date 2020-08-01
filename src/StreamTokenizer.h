#pragma once

#include "IStreamTokenizer.h"
#include "TextFormatterDefs.h"

namespace vtf
{

class StreamTokenizer : public IStreamTokenizer
{
public:
	StreamTokenizer() = default;

	void processStream(std::istream& i_stream);

private:
	struct token_data
	{
	public:
		token_data() = default;

		void add_data(TokenType i_type, char i_data);
		void clear();

		bool empty() const;
		token get(size_t i_tokenCounter) const;

	private:
		TokenType m_type = TokenType::None;
		std::string m_data;
	};

	token_data m_currToken;
	size_t m_tokenCounter = 0;
};

}