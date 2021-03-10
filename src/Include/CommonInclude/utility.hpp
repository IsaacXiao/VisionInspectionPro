#ifndef UTILITY_H
#define UTILITY_H

#include <regex>
#include <iterator>
#include <iostream>
#include <type_traits>

inline bool RegCheck(std::string &&exp, const std::regex& reg) noexcept
{
	return std::regex_match(exp, reg);
}

template<typename ItorT>
void print_container(const ItorT first, const ItorT last, const char* separate = " ") noexcept
{
	//typedef typename iterator_traits<ItorT>::value_type Ty;
	std::copy( first, last, std::ostream_iterator<decltype(*first)>( std::cout, separate ) );
	std::cout << std::endl;
}

template<typename E>
constexpr typename std::underlying_type<E>::type EnumToInt(E enumerator) noexcept
{
	return static_cast<typename std::underlying_type<E>::type>(enumerator);
}

#endif