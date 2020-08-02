#pragma once

#include "ScannerDefs.h"

namespace vtf
{

enum class NumberPos
{
	Zero = 0,
	One,
	Two,
	Three,
	Four,
	Five,
	Six,
	Seven,
	Eight,
	Nine,
	Ten,
	Eleven,
	Twelve,
	Thirteen,
	Fourteen,
	Fifteen,
	Sixteen,
	Seventeen,
	Eighteen,
	Nineteen,
	Twenty,
	Thirty = 30,
	Fourty = 40,
	Fifty = 50,
	Sixty = 60,
	Seventy = 70,
	Eighty = 80,
	Ninety = 90
};

enum class NumberMultiplier
{
	None = 0,
	Hundred = 2,
	Thousand = 3,
	HundredThousand = 5,
	Million = 6,
	HundredMillion = 8,
	Billion = 9
};

struct number_intermediate_representation : detail::intermediate_representation_impl
{
	typedef std::vector<std::pair<NumberPos,NumberMultiplier>> number_container;

public:
	typedef number_container::iterator iterator;
	typedef number_container::const_iterator const_iterator;
	typedef number_container::reverse_iterator reverse_iterator;
	typedef number_container::const_reverse_iterator const_reverse_iterator;

	number_intermediate_representation(unsigned int m_maxMultiplier);

	void add(NumberPos i_number);
	bool try_set_multiplier(NumberMultiplier i_multiplier);
	bool empty() const;
	size_t size() const;

	void clear();
	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();
	const_iterator begin() const;
	const_iterator end() const;
	const_reverse_iterator rbegin() const;
	const_reverse_iterator rend() const;

private:
	std::vector<std::pair<NumberPos,NumberMultiplier>> m_tokens;
	const unsigned int m_maxMultiplier;
};

}