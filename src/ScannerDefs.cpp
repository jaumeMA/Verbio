#include "ScannerDefs.h"

namespace vtf
{

intermediate_representation::intermediate_representation()
: m_impl(nullptr)
{
}
intermediate_representation::intermediate_representation(intermediate_representation&& other)
: m_impl(nullptr)
{
	std::swap(m_impl,other.m_impl);
}
intermediate_representation::~intermediate_representation()
{
	if (m_impl)
	{
		delete m_impl;
	}
}
bool intermediate_representation::empty() const
{
	return m_impl == nullptr;
}

std::vector<std::string> default_intermdiate_representation::acquire()
{
	return std::move(m_acceptedTokens);
}
void default_intermdiate_representation::add(const std::string& i_token)
{
	m_acceptedTokens.push_back(i_token);
}
size_t default_intermdiate_representation::size() const
{
	return m_acceptedTokens.size();
}
bool default_intermdiate_representation::empty() const
{
	return m_acceptedTokens.empty();
}
default_intermdiate_representation::iterator default_intermdiate_representation::begin()
{
	return m_acceptedTokens.begin();
}
default_intermdiate_representation::iterator default_intermdiate_representation::end()
{
	return m_acceptedTokens.end();
}
default_intermdiate_representation::const_iterator default_intermdiate_representation::begin() const
{
	return m_acceptedTokens.begin();
}
default_intermdiate_representation::const_iterator default_intermdiate_representation::end() const
{
	return m_acceptedTokens.end();
}

}