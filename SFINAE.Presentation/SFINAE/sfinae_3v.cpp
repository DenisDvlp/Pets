#pragma once

//true-false

struct True { using result = True; };

struct False { using result = False; };

template <typename T>
using get_result = typename T::result;

//is_vector

template <typename T, typename = void>
struct is_container_impl : False {};

template <typename T>
struct is_container_impl<T, decltype(typename T::value_type(), void()) > : True {};

template <typename T>
using is_container = get_result<is_container_impl<T>>;

//is_const

template <typename T>
struct is_const_impl : False {};

template <typename T>
struct is_const_impl<const T> : True {};

template <typename T>
using is_const = get_result<is_const_impl<T>>;

//And

template <typename T1, typename T2>
struct And_impl : False {};

template <>
struct And_impl <True, True> : True {};

template <typename T1, typename T2>
using And = get_result<And_impl<T1, T2>>;

//Not

template <typename T>
struct Not_impl : False {};

template <>
struct Not_impl <False> : True {};

template <typename T>
using Not = get_result<Not_impl<T>>;

//If

template <typename T>
struct If_impl;

template <>
struct If_impl<True> { using allow = void; };

template <typename T>
using If = typename If_impl<T>::allow;


//function template

template<typename T, typename = If<And<is_container<T>, Not<is_const<T>>>>>
void f(T& t)
{

}