#pragma once

#include <memory>
#include "IScannerRuleAcceptor.h"
#include "IScannerRuleTransformer.h"

namespace vtf
{

class ScannerRule
{
public:
	ScannerRule(std::unique_ptr<IScannerRuleAcceptor> i_acceptor, std::unique_ptr<IScannerRuleTransformer> i_transformer);
	ScannerRule(const ScannerRule&) = delete;
	ScannerRule(ScannerRule&& other);

	bool accept(const token& i_token) const;
	std::string acquire_match();
	match_degree get_match_degree() const;
	void clear();

private:
	mutable std::unique_ptr<IScannerRuleAcceptor> m_acceptor;
	mutable std::unique_ptr<IScannerRuleTransformer> m_transformer;
};

}