//sfinae.h
#pragma once
#include <iterator>

// base

struct not_a_type {};

template <typename T>
constexpr bool static_assert_false = false;

template <bool Value> struct Bool { static constexpr bool value = Value; };
using True = Bool<true>;
using False = Bool<false>;

template<bool value> struct IF_impl {};
template<> struct IF_impl<true> { using result = not_a_type; };
template<bool value> using IF = typename IF_impl<value>::result;

template<typename T> struct unvolatile_impl { using type = T; };
template<typename T> struct unvolatile_impl<volatile T> { using type = T; };
template<typename T> using  unv = typename unvolatile_impl<T>::type;

template<typename T> struct unconst_impl { using type = T; };
template<typename T> struct unconst_impl<const T> { using type = T; };
template<typename T> using  unc = typename unconst_impl<T>::type;

template<typename T> struct unpointer_impl { using type = T; };
template<typename T> struct unpointer_impl<T*> { using type = T; };
template<typename T> struct unpointer_impl<T* const> { using type = T; };
template<typename T> struct unpointer_impl<T* volatile> { using type = T; };
template<typename T> struct unpointer_impl<T* const volatile> { using type = T; };
template<typename T> using  unpointer = typename unpointer_impl<T>::type;

template<typename T> struct unreference_impl { using type = T; };
template<typename T> struct unreference_impl<T&> { using type = T; };
template<typename T> struct unreference_impl<T&&> { using type = T; };
template<typename T> using  unref = typename unreference_impl<T>::type;

template<typename T> using  uncv = unc<unv<T>>;

template<typename T> using  uncvref = uncv<unref<T>>;

template<typename T> using  pure = uncv<unpointer<unref<T>>>;

template<typename... T> using Void = void;

// feature detector

template<template<typename...>typename T, typename, typename... Args>
struct feature_detector_impl : False {};
template<template<typename...>typename T, typename... Args>
struct feature_detector_impl<T, Void<T<Args...>>, Args...> : True {};
template<template<typename...>typename T, typename... Args>
using feature_detector = feature_detector_impl<T, void, Args...>;
template<template<typename...>typename T, typename... Args>
constexpr bool feature_detected = feature_detector<T, Args...>::value;

// declval

template<typename T, typename = void> struct rref_impl { using type = T; };
template<typename T> struct rref_impl<T, Void<T&>> { using type = T &&; };
template<typename T> using  rref = typename rref_impl<T>::type;
template<typename T> rref<T> val() noexcept;

// conditions

template<typename T1, typename T2> struct is_same_impl : False {};
template<typename T> struct is_same_impl<T, T> : True {};
template<typename T1, typename T2> constexpr bool is_same = is_same_impl<pure<T1>, pure<T2>>::value;

template<typename T1, typename T2> struct is_exact_impl : False {};
template<typename T> struct is_exact_impl<T, T> : True {};
template<typename T1, typename T2> constexpr bool is_exact = is_exact_impl<T1, T2>::value;

template<typename T> struct is_ptr_impl : False {};
template<typename T> struct is_ptr_impl<T*> : True {};
template<typename T> struct is_ptr_impl<T* const> : True {};
template<typename T> struct is_ptr_impl<T* volatile> : True {};
template<typename T> struct is_ptr_impl<T* const volatile> : True {};
template<typename T> constexpr bool is_ptr = is_ptr_impl<T>::value;

template<typename T> struct is_const_impl : False {};
template<typename T> struct is_const_impl<const T> : True {};
template<typename T> constexpr bool is_const = is_const_impl<T>::value;


template<typename T> struct is_rref_impl : False {};
template<typename T> struct is_rref_impl<T&&> : True {};
template<typename T> constexpr bool is_rref = is_rref_impl<T>::value;

template<typename T> struct is_lref_impl : False {};
template<typename T> struct is_lref_impl<T&> : True {};
template<typename T> constexpr bool is_lref = is_lref_impl<T>::value;

template<typename T> constexpr bool is_ref = is_rref<T> || is_lref<T>;

template<typename T> struct is_volatile_impl : False {};
template<typename T> struct is_volatile_impl<volatile T> : True {};
template<typename T> constexpr bool is_volatile = is_volatile_impl<T>::value;

template<typename T1, typename T2>
struct is_convertable_impl
{
    static auto test(T1) { return True(); }
    static auto test(...) { return False(); }
    static constexpr bool value = decltype(test(val<T2>()))::value;
};
template<typename T1, typename T2> constexpr bool is_convertible = is_convertable_impl<T1, T2>::value;

template<typename T, typename R = void, typename... Args> struct is_method_impl : False {};
template<typename T, typename R, typename... Args> struct is_method_impl<R(T::*)(Args...)> : True {};
template<typename T> constexpr bool is_method = is_method_impl<T>::value;

template<typename R, typename... Args> struct is_function_impl : False {};
template<typename R, typename... Args> struct is_function_impl<R(Args...)> : True {};
template<typename R, typename... Args> struct is_function_impl<R(*)(Args...)> : True {};
template<typename T> constexpr bool is_function = is_function_impl<T>::value;

template<typename T> using has_operator_parantheses = decltype(&T::operator());
template<typename T> constexpr bool is_functor = feature_detected<has_operator_parantheses, T>;

template<typename T> constexpr bool is_callable = is_function<T> || is_functor<T>;

template<typename T, typename R, typename... Args>
using has_signature_impl = IF<is_same<decltype(val<T>()(val<Args>()...)), R>>;
template<typename T, typename R, typename... Args>
struct is_callable_match_impl : feature_detector<has_signature_impl, T, R, Args...> {};
template <typename T, typename R, typename... Args>
constexpr bool is_callable_match = is_callable_match_impl<T, R, Args...>::value;

// arrays

template<typename T> struct array_impl : False { static constexpr size_t size = 0; using type = not_a_type; };
template<typename T, size_t S> struct array_impl <T[S]> : True { static constexpr size_t size = S; using type = T; };
template<typename T, size_t S> struct array_impl <T(&)[S]> : True { static constexpr size_t size = S; using type = T; };
template<typename T, size_t S> struct array_impl <T(&&)[S]> : True { static constexpr size_t size = S; using type = T; };
template<typename T> using array_type = typename array_impl<T>::type;
template<typename T> constexpr size_t array_size = array_impl<T>::size;
template<typename T> constexpr bool is_array = array_impl<T>::value;

// containers

template<typename T> using has_value_type_impl = typename T::value_type;
template<typename T> constexpr bool has_value_type = feature_detected<has_value_type_impl, T>;

template<typename T> using has_iterator_impl = typename T::iterator;
template<typename T> constexpr bool has_iterator = feature_detected<has_iterator_impl, T>;

template<typename T> using has_const_iterator_impl = typename T::const_iterator;
template<typename T> constexpr bool has_const_iterator = feature_detected<has_const_iterator_impl, T>;

template<typename T> using has_allocator_type_impl = typename T::allocator_type;
template<typename T> constexpr bool has_allocator_type = feature_detected<has_allocator_type_impl, T>;

template<typename T> using has_key_type_impl = typename T::key_type;
template<typename T> constexpr bool has_key_type = feature_detected<has_key_type_impl, T>;

template<typename TAG, typename T>
constexpr bool check_iterator = is_convertible<TAG, T>;

template<typename TAG, typename T>
using is_iterator_category_impl = IF<check_iterator<TAG, typename T::iterator::iterator_category>>;
template<typename TAG, typename T> constexpr bool is_iterator_category = feature_detected<is_iterator_category_impl, TAG, T>;

template <typename T> constexpr bool is_iterator_input = is_iterator_category<std::input_iterator_tag, T>;
template <typename T> constexpr bool is_iterator_forward = is_iterator_category<std::forward_iterator_tag, T>;
template <typename T> constexpr bool is_iterator_bidirectional = is_iterator_category<std::bidirectional_iterator_tag, T>;
template <typename T> constexpr bool is_iterator_random = is_iterator_category<std::random_access_iterator_tag, T>;

template<typename T> constexpr bool is_container = has_value_type<T> && has_iterator<T> && has_const_iterator<T>;
template<typename T> constexpr bool is_container_dynamic = is_container<T> && has_allocator_type<T>;
template<typename T> constexpr bool is_container_static = is_container<T> && !has_allocator_type<T>;
template<typename T> constexpr bool is_container_sequential = is_container<T> && !has_key_type<T>;
template<typename T> constexpr bool is_container_tree = is_container<T> && has_key_type<T>;

template<typename T> using has_method_reserve_impl = decltype(&T::reserve);
template<typename T> constexpr bool has_method_reserve = feature_detected<has_method_reserve_impl, T>;

template<typename T> using has_method_remove_impl = decltype(&T::remove);
template<typename T> constexpr bool has_method_remove = feature_detected<has_method_remove_impl, T>;

template<typename T, typename... Args> using has_method_sort_impl = decltype(val<T>().sort(Args()...));
template<typename T, typename... Args> constexpr bool has_method_sort = feature_detected<has_method_sort_impl, T, Args...>;

template<typename T> using has_method_reverse_impl = decltype(&T::reverse);
template<typename T> constexpr bool has_method_reverse = feature_detected<has_method_reverse_impl, T>;

template<typename T> using has_method_base_impl = decltype(&T::base);
template<typename T> constexpr bool has_method_base = feature_detected<has_method_base_impl, T>;

template<typename T> using has_method_data_impl = decltype(std::declval<T>().data());
template<typename T> constexpr bool has_method_data = feature_detected<has_method_data_impl, T>;

template<typename T, typename... Args> using has_method_emplace_impl = decltype(&T::template emplace<Args...>);
template<typename T, typename... Args> constexpr bool has_method_emplace = feature_detected<has_method_emplace_impl, T, Args...>;

template<typename T, typename = void> struct get_value_type_impl { using type = not_a_type; };
template<typename T> struct get_value_type_impl <T, Void<typename T::value_type>> { using type = typename T::value_type; };
template<typename T> using get_value_type = typename get_value_type_impl<unref<T>>::type;