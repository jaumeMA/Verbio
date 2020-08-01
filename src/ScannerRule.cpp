#include "ScannerRule.h"

namespace vtf
{

ScannerRule::ScannerRule(std::unique_ptr<IScannerRuleAcceptor> i_acceptor, std::unique_ptr<IScannerRuleTransformer> i_transformer)
: m_acceptor(std::move(i_acceptor))
, m_transformer(std::move(i_transformer))
{
}
ScannerRule::ScannerRule(ScannerRule&& other)
: m_acceptor(std::move(other.m_acceptor))
, m_transformer(std::move(other.m_transformer))
{
}
bool ScannerRule::accept(const token& i_token) const
{
	if (m_acceptor)
	{
		return m_acceptor->accept(i_token);
	}
	else
	{
		return false;
	}
}
std::string ScannerRule::acquire_match()
{
	if (m_acceptor && m_transformer)
	{
		return m_transformer->transform(m_acceptor->acquire_match());
	}
	else
	{
		return "";
	}
}
void ScannerRule::clear()
{
	if (m_acceptor)
	{
		m_acceptor->clear();
	}
}
match_degree ScannerRule::get_match_degree() const
{
	if (m_acceptor)
	{
		return m_acceptor->get_match_degree();
	}
	else
	{
		return k_invalidDegree;
	}
}

}