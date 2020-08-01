#pragma once

#include <string>
#include <vector>

namespace vtf
{
namespace detail
{

struct intermediate_representation_impl
{
public:
	virtual ~intermediate_representation_impl() = default;
};

}

struct bad_intermediate_representation : std::exception
{
};

struct intermediate_representation
{
public:
	intermediate_representation();
	template<typename T>
	intermediate_representation(T&& i_intermediateRepresentation)
	{
		typedef typename std::remove_reference<T>::type rawT;

		static_assert(std::is_base_of<detail::intermediate_representation_impl,rawT>::value, "You shall provide a base of detail::intermediate_representation_impl");

		m_impl = new rawT(std::move(i_intermediateRepresentation));
	}
	intermediate_representation(const intermediate_representation&) = delete;
	intermediate_representation(intermediate_representation&& other);
	~intermediate_representation();

	intermediate_representation& operator=(const intermediate_representation&) = delete;
	intermediate_representation& operator=(intermediate_representation&&) = delete;

	bool empty() const;

	template<typename T>
	T acquire()
	{
		static_assert(std::is_base_of<detail::intermediate_representation_impl,T>::value, "You shall provide a base of detail::intermediate_representation_impl");

		if (T* impl = dynamic_cast<T*>(m_impl))
		{
			T res(std::move(*impl));

			delete m_impl;
			m_impl = nullptr;

			return std::move(res);
		}
		else
		{
			throw bad_intermediate_representation();
		}
	}

private:
	detail::intermediate_representation_impl* m_impl;
};

struct default_intermdiate_representation : detail::intermediate_representation_impl
{
public:
	typedef std::vector<std::string>::iterator iterator;
	typedef std::vector<std::string>::const_iterator const_iterator;

	default_intermdiate_representation() = default;

	std::vector<std::string> acquire();
	void add(const std::string& i_token);
	size_t size() const;
	bool empty() const;
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

private:
	std::vector<std::string> m_acceptedTokens;
};

typedef size_t match_degree;

const match_degree k_invalidDegree = -1;

}