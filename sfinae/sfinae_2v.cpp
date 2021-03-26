#pragma once

//true-false

struct True { using result = True; };

struct False { using result = False; };

//is_vector

template <typename T, typename = void>
struct is_container : False {};

template <typename T>
struct is_container<T, decltype(typename T::value_type(), void()) > : True {};

//is_const

template <typename T>
struct is_const : False {};

template <typename T>
struct is_const<const T> : True {};

//And

template <typename T1, typename T2>
struct And : False {};

template <>
struct And <True, True> : True {};

//Not

template <typename T>
struct Not : False {};

template <>
struct Not <False> : True {};

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
void f(T& t)
{

}
