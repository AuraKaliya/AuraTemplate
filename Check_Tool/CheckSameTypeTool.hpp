#pragma once
#include <type_traits>

template<typename T,typename... Ts>
constexpr bool isSameType()
{
	return (std::is_same_v<T,Ts> &&...);
}