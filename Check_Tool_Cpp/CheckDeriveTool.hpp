#pragma once
#include <type_traits>
template <typename Derived, typename Base>
struct IsDerivedFrom {
    static constexpr bool value = std::is_base_of<Base, Derived>::value;
};