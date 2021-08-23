#pragma once

//true-false

struct True {};

struct False {};

//is_vector

template <typename T, typename = void>
struct is_container { using result = False; };

template <typename T>
struct is_container<T, decltype(typename T::value_type(), void()) > { using result = True; };

//is_const

template <typename T>
struct is_const { using result = False; };

template <typename T>
struct is_const<const T> { using result = True; };

//And

template <typename T1, typename T2>
struct And { using result = False; };

template <>
struct And <True, True> { using result = True; };

//Not

template <typename T>
struct Not { using result = False; };

template <>
struct Not <False> { using result = True; };

//If

template <typename T>
struct If;

template <>
struct If<True> { using allow = void; };


//function template

template<typename T, typename =
    typename If<
        typename And<
            typename is_container<T>::result,
            typename Not< typename is_const<T>::result >::result
        >::result
    >::allow
>
void f(T & t)
{

}