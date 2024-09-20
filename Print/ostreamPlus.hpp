#include <iostream>
#include <tuple>
#include <utility>

template<typename... Ts>
std::ostream& operator<<(std::ostream& os, std::tuple<Ts...> const& theTuple)
{
    std::apply
    (
        [&os](Ts const&... tupleArgs)
        {
            os << '[';
            std::size_t n{ 0 };
            (..., (os << tupleArgs << (++n != sizeof...(Ts) ? "," : "")));
            os << ']';
        }, theTuple
    );
    return os;
}