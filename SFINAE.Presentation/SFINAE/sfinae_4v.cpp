#pragma once

//true-false

template <bool value>
struct Bool { static constexpr bool result = value; };

using True = Bool<true>;

using False = Bool<false>;

template <typename T>
constexpr bool get_result = T::result;

template <typename T>
using Void = void;

//is_vector

template <typename T, typename = void>
struct is_container_impl : False {};

template <typename T>
struct is_container_impl<T, Void<typename T::value_type>> : True {};

template <typename T>
constexpr bool is_container = get_result<is_container_impl<T>>;

//is_const

template <typename T>
struct is_const_impl : False {};

template <typename T>
struct is_const_impl<const T> : True {};

template <typename T>
constexpr bool is_const = get_result<is_const_impl<T>>;

//If

template <bool value>
struct If_impl;

template <>
struct If_impl<true> { using allow = void; };

template <bool value>
using If = typename If_impl<value>::allow;


//function template

template<typename T, typename = If<is_container<T> && !is_const<T>>>
void f(T& t)
{

}
