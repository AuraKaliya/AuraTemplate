#pragma once
#include <tuple>
#include <functional>
#include <type_traits>
#include <memory>

/* use c17  by Aura 2024.8.20*/

//去掉成员指针 / 类域
template<typename T>
struct remove_member_pointer;

template<typename ClassType, typename MemberType>
struct remove_member_pointer<MemberType ClassType::*> {
    using type = MemberType;
};
template<typename T>
using remove_member_pointer_t = typename remove_member_pointer<T>::type;



#define REGISTER_FUNCTION_FOR_CHECK(Function) template<typename T, typename R, typename... Args>\
struct has_##Function {\
private:template<typename U, typename = decltype(std::declval<U>().##Function(std::declval<Args>()...))>\
    static constexpr std::true_type check(T*);\
    template<typename>static constexpr std::false_type check(...);\
    template<typename U> static constexpr auto check_return_type(U*) -> typename std::is_same<decltype(std::declval<U>().##Function(std::declval<Args>()...)), R>::type;\
    template<typename>static constexpr std::false_type check_return_type(...);\
public:static constexpr bool value = decltype(check<T>(0))::value &&decltype(check_return_type<T>(0))::value;\
template<typename... Args>\
has_##Function(Args&&... args){};\
};

#define CHECK_FUNCTION_EXIST(ObjClass, Function, RetClass, ...)                       \
    std::apply( [](auto&&...args)constexpr{                                                   \
        using Class_Function = has_##Function<ObjClass, RetClass,decltype(args)...>; \
        return Class_Function::value;                                               \
    }, std::tuple<__VA_ARGS__>{})

#define REGISTER_PROPERTY_FOR_CHECK(Property) template<typename Class, typename T>\
struct has_##Property { \
private: \
template<typename C,typename =decltype(std::declval<C>().##Property)>\
static constexpr std::true_type check(Class*);\
template<typename>static constexpr std::false_type check(...);\
template<typename C> \
static constexpr auto check_type(C*) ->typename std::is_same<decltype(std::declval<C>().##Property),T>::type;\
public:\
static constexpr bool value = decltype(check<Class>(0))::value && decltype(check_type<Class>(0))::value; \
};

#define CHECK_PROPERTY_EXIST(ObjClass,Property,PropertyClass) \
has_##Property<ObjClass,PropertyClass>::value

#define CHECK_PROPERTY_EXIST_ONLY_NAME(ObjClass,Property) \
has_##Property<ObjClass,remove_member_pointer_t<decltype(&ObjClass::Property)> >::value



