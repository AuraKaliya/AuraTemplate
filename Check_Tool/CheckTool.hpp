#pragma once
#include <tuple>
#include <functional>
#include <type_traits>
#include <memory>

/* use c17  by Aura 2024.8.20*/
#define REGISTER_FUNCTION_FOR_CHECK(Function) template<typename T, typename R, typename... Args>\
struct has_##Function {\
private:template<typename T, typename = decltype(std::declval<T>().##Function(std::declval<Args>()...))>\
    static constexpr std::true_type check(T*);\
    template<typename>static constexpr std::false_type check(...);\
    template<typename T> static constexpr auto check_return_type(T*) -> typename std::is_same<decltype(std::declval<T>().##Function(std::declval<Args>()...)), R>::type;\
    template<typename>static constexpr std::false_type check_return_type(...);\
public:static constexpr bool value = decltype(check<T>(0))::value &&decltype(check_return_type<T>(0))::value;\
template<typename... Args>\
has_##Function(Args&&... args){};\
};

#define CHECK_FUNCTION_EXIST(ObjClass, Function, RetClass, ...)                       \
    std::apply( [](auto&&...args){                                                   \
        using Class_Function = has_##Function<ObjClass, RetClass,decltype(args)...>; \
        return Class_Function::value;                                               \
    }, std::tuple<__VA_ARGS__>{})

#define REGISTER_PROPERTY_FOR_CHECK(Property) template<typename Class, typename T>\
struct has_##Property { \
private: \
template<typename Class,typename =decltype(std::declval<Class>().##Property)>\
static constexpr std::true_type check(Class*);\
template<typename>static constexpr std::false_type check(...);\
template<typename Class> \
static constexpr auto check_type(Class*) ->typename std::is_same<decltype(std::declval<Class>().##Property),T>::type;\
public:\
static constexpr bool value = decltype(check<Class>(0))::value && decltype(check_type<Class>(0))::value; \
};

#define CHECK_PROPERTY_EXIST(ObjClass,Property,PropertyClass) \
has_##Property<ObjClass,PropertyClass>::value


