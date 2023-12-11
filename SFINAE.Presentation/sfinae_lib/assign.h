MIT License

Copyright (c) 2023 Denys Petrov

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once
#include "sfinae.h"
#include <type_traits>

template<typename Container, typename Source>
void assign(Container& container, Source&& source)
{
}


template <typename...> using void_t = void;
template <typename T, typename U> constexpr bool is_same_v = std::is_same<T, U>::value;
template <typename T> struct get_member {};
template <typename T, typename O> struct get_member<T O::*> { using type = T; };
template <typename T> using get_member_t = typename get_member<T>::type;
template <typename T> struct get_owner {};
template <typename T, typename O> struct get_owner<T O::*> { using type = O; };
template <typename T> using get_owner_t = typename get_owner<T>::type;
template <typename T> constexpr bool is_member_object_pointer_v = std::is_member_object_pointer<T>::value;
template <typename B, typename D> constexpr bool is_base_of_v = std::is_base_of<B, D>::value;

template <typename T> using general_container_traits = void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end()),
              decltype(std::declval<T>().size()), decltype(std::declval<T>().empty()),
              typename T::iterator, typename T::const_iterator, typename T::value_type>;
template <typename T> using associative_container_traits = void_t<typename T::key_type>;
template <typename T> using ordered_associative_container_traits = void_t<typename T::key_compare, typename T::value_compare>;
template <typename T> using unordered_associative_container_traits = void_t<typename T::hasher, typename T::key_equal>;
template <typename T> using map_container_traits = void_t<typename T::mapped_type>;

template <typename T, typename V = void> struct has_general_container_traits : std::false_type {};
template <typename T> struct has_general_container_traits<T, general_container_traits<T>> : std::true_type {};
template<typename T> constexpr bool has_general_container_traits_v = has_general_container_traits<T>::value;

template <typename T, typename V = void> struct has_associative_container_traits : std::false_type {};
template <typename T> struct has_associative_container_traits<T, associative_container_traits<T>> : std::true_type {};
template<typename T> constexpr bool has_associative_container_traits_v = has_associative_container_traits<T>::value;

template <typename T, typename V = void> struct has_ordered_associative_container_traits : std::false_type {};
template <typename T> struct has_ordered_associative_container_traits<T, ordered_associative_container_traits<T>> : std::true_type {};
template<typename T> constexpr bool has_ordered_associative_container_traits_v = has_ordered_associative_container_traits<T>::value;

template <typename T, typename V = void> struct has_unordered_associative_container_traits : std::false_type {};
template <typename T> struct has_unordered_associative_container_traits<T, unordered_associative_container_traits<T>> : std::true_type {};
template<typename T> constexpr bool has_unordered_associative_container_traits_v = has_unordered_associative_container_traits<T>::value;

template <typename T, typename V = void> struct has_map_container_traits : std::false_type {};
template <typename T> struct has_map_container_traits<T, map_container_traits<T>> : std::true_type {};
template<typename T> constexpr bool has_map_container_traits_v = has_map_container_traits<T>::value;

template<typename T> constexpr bool is_any_container_v = has_general_container_traits_v<T>;
template<typename T> constexpr bool is_sequantial_container_v = has_general_container_traits_v<T> && !has_associative_container_traits_v<T>;
template<typename T> constexpr bool is_associative_container_v = has_general_container_traits_v<T> && has_associative_container_traits_v<T>;
template<typename T> constexpr bool is_ordered_associative_container_v = is_associative_container_v<T> && has_ordered_associative_container_traits_v<T>;
template<typename T> constexpr bool is_unordered_associative_container_v = is_associative_container_v<T> && has_unordered_associative_container_traits_v<T>;
template<typename T> constexpr bool is_set_v = is_associative_container_v<T> && !has_map_container_traits_v<T>;
template<typename T> constexpr bool is_map_v = is_associative_container_v<T> && has_map_container_traits_v<T>;
template<typename T> constexpr bool is_ordered_set_container_v = is_ordered_associative_container_v<T> && !has_map_container_traits_v<T>;
template<typename T> constexpr bool is_ordered_map_container_v = is_ordered_associative_container_v<T> && has_map_container_traits_v<T>;


namespace details {
template<typename T, typename A> struct forward_member_helper { using type = traits::remove_const_reference_t<A>&&; };
template<typename T, typename A> struct forward_member_helper<T&, A> { using type = traits::remove_const_reference_t<A>&; };
template<typename T, typename A> struct forward_member_helper<const T&, A> { using type = const traits::remove_const_reference_t<A>&; };
template<typename T, typename A> using forward_member_helper_t = typename forward_member_helper<T, A>::type;
}
template<typename T, typename A>
decltype(auto) forward_member(A&& another) {
    return static_cast<details::forward_member_helper_t<T, A>>(another);
}

template<typename T> constexpr bool is_unordered_set_container_v = is_unordered_associative_container_v<T> && !has_map_container_traits_v<T>;
template<typename T> constexpr bool is_unordered_map_container_v = is_unordered_associative_container_v<T> && has_map_container_traits_v<T>;
#pragma once
#include "sfinae.h"
#include <type_traits>

template<typename Container, typename Source>
void assign(Container& container, Source&& source)
{
}


template <typename...> using void_t = void;
template <typename T, typename U> constexpr bool is_same_v = std::is_same<T, U>::value;
template <typename T> struct get_member {};
template <typename T, typename O> struct get_member<T O::*> { using type = T; };
template <typename T> using get_member_t = typename get_member<T>::type;
template <typename T> struct get_owner {};
template <typename T, typename O> struct get_owner<T O::*> { using type = O; };
template <typename T> using get_owner_t = typename get_owner<T>::type;
template <typename T> constexpr bool is_member_object_pointer_v = std::is_member_object_pointer<T>::value;
template <typename B, typename D> constexpr bool is_base_of_v = std::is_base_of<B, D>::value;

template <typename T> using general_container_traits = void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end()),
              decltype(std::declval<T>().size()), decltype(std::declval<T>().empty()),
              typename T::iterator, typename T::const_iterator, typename T::value_type>;
template <typename T> using associative_container_traits = void_t<typename T::key_type>;
template <typename T> using ordered_associative_container_traits = void_t<typename T::key_compare, typename T::value_compare>;
template <typename T> using unordered_associative_container_traits = void_t<typename T::hasher, typename T::key_equal>;
template <typename T> using map_container_traits = void_t<typename T::mapped_type>;

template <typename T, typename V = void> struct has_general_container_traits : std::false_type {};
template <typename T> struct has_general_container_traits<T, general_container_traits<T>> : std::true_type {};
template<typename T> constexpr bool has_general_container_traits_v = has_general_container_traits<T>::value;

template <typename T, typename V = void> struct has_associative_container_traits : std::false_type {};
template <typename T> struct has_associative_container_traits<T, associative_container_traits<T>> : std::true_type {};
template<typename T> constexpr bool has_associative_container_traits_v = has_associative_container_traits<T>::value;

template <typename T, typename V = void> struct has_ordered_associative_container_traits : std::false_type {};
template <typename T> struct has_ordered_associative_container_traits<T, ordered_associative_container_traits<T>> : std::true_type {};
template<typename T> constexpr bool has_ordered_associative_container_traits_v = has_ordered_associative_container_traits<T>::value;

template <typename T, typename V = void> struct has_unordered_associative_container_traits : std::false_type {};
template <typename T> struct has_unordered_associative_container_traits<T, unordered_associative_container_traits<T>> : std::true_type {};
template<typename T> constexpr bool has_unordered_associative_container_traits_v = has_unordered_associative_container_traits<T>::value;

template <typename T, typename V = void> struct has_map_container_traits : std::false_type {};
template <typename T> struct has_map_container_traits<T, map_container_traits<T>> : std::true_type {};
template<typename T> constexpr bool has_map_container_traits_v = has_map_container_traits<T>::value;

template<typename T> constexpr bool is_any_container_v = has_general_container_traits_v<T>;
template<typename T> constexpr bool is_sequantial_container_v = has_general_container_traits_v<T> && !has_associative_container_traits_v<T>;
template<typename T> constexpr bool is_associative_container_v = has_general_container_traits_v<T> && has_associative_container_traits_v<T>;
template<typename T> constexpr bool is_ordered_associative_container_v = is_associative_container_v<T> && has_ordered_associative_container_traits_v<T>;
template<typename T> constexpr bool is_unordered_associative_container_v = is_associative_container_v<T> && has_unordered_associative_container_traits_v<T>;
template<typename T> constexpr bool is_set_v = is_associative_container_v<T> && !has_map_container_traits_v<T>;
template<typename T> constexpr bool is_map_v = is_associative_container_v<T> && has_map_container_traits_v<T>;
template<typename T> constexpr bool is_ordered_set_container_v = is_ordered_associative_container_v<T> && !has_map_container_traits_v<T>;
template<typename T> constexpr bool is_ordered_map_container_v = is_ordered_associative_container_v<T> && has_map_container_traits_v<T>;


namespace details {
template<typename T, typename A> struct forward_member_helper { using type = traits::remove_const_reference_t<A>&&; };
template<typename T, typename A> struct forward_member_helper<T&, A> { using type = traits::remove_const_reference_t<A>&; };
template<typename T, typename A> struct forward_member_helper<const T&, A> { using type = const traits::remove_const_reference_t<A>&; };
template<typename T, typename A> using forward_member_helper_t = typename forward_member_helper<T, A>::type;
}
template<typename T, typename A>
decltype(auto) forward_member(A&& another) {
    return static_cast<details::forward_member_helper_t<T, A>>(another);
}

template<typename T> constexpr bool is_unordered_set_container_v = is_unordered_associative_container_v<T> && !has_map_container_traits_v<T>;
template<typename T> constexpr bool is_unordered_map_container_v = is_unordered_associative_container_v<T> && has_map_container_traits_v<T>;
