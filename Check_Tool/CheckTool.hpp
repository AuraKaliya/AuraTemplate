#pragma once
#include <memory>

#define REGISTERFUNCTIONFORCHECK(Function)  \
template<typename T, typename R, typename... Args>\
struct has_##Function {\
private:template<typename U, typename = decltype(std::declval<U>().##Function(std::declval<Args>()...))>\
    static constexpr std::true_type check(U*);\
    template<typename>static constexpr std::false_type check(...);\
    template<typename U> static constexpr auto check_return_type(U*) -> typename std::is_same<decltype(std::declval<U>().is_init(std::declval<Args>()...)), R>::type;\
    template<typename>static constexpr std::false_type check_return_type(...);\
public:static constexpr bool value = decltype(check<T>(0))::value &&decltype(check_return_type<T>(0))::value;\
};

#define CHECKCLASSFUNCTION(ObjClass, Function, RetClass, ...)                       \
    []()-> auto {                                                                   \
        using Class_Function = has_##Function<ObjClass,RetClass ,##__VA_ARGS__>;    \
        return Class_Function::value;                                               \
    }()