#pragma once

template <typename T>
constexpr bool static_assert_false = false;

// Bool

template <bool Value> struct Bool { static constexpr bool value = Value; };
using True = Bool<true>;
using False = Bool<false>;

// If

template<bool value, typename T> struct IF_impl {};
template<typename T> struct IF_impl<true, T> { using type = T; };
template<bool value, typename T = void> using IF = typename IF_impl<value, T>::type;

// Predicates

template <typename T> struct IsConstImpl : False {};
template <typename T> struct IsConstImpl <const T> : True {};
template <typename T> constexpr bool IsConst = IsConstImpl <T>::value;

template <typename T> struct IsLReferenceImpl : False { };
template <typename T> struct IsLReferenceImpl <T&> : True { };
template <typename T> constexpr bool IsLReference = IsLReferenceImpl <T>::value;

template <typename T> struct IsRReferenceImpl : False { };
template <typename T> struct IsRReferenceImpl <T&&> : True { };
template <typename T> constexpr bool IsRReference = IsRReferenceImpl <T>::value;

template <typename T> constexpr bool IsReference = IsLReference<T> || IsRReference<T>;

template <typename T> using Wrap = void;

template <typename T, typename = void> struct HasMethodFooImpl : False { };
template <typename T> struct HasMethodFooImpl <T, Wrap <decltype(&T::foo)> > : True { };
template <typename T> constexpr bool HasMethodFoo = HasMethodFooImpl <T>::value;

// Modifiers

template <typename T> struct RemoveConstImpl { using result = T; };
template <typename T> struct RemoveConstImpl <const T> { using result = T; };
template <typename T> using RemoveConst = typename RemoveConstImpl <T>::result;

template <typename T> struct RemoveReferenceImpl { using result = T; };
template <typename T> struct RemoveReferenceImpl <T&> { using result = T; };
template <typename T> struct RemoveReferenceImpl <T&&> { using result = T; };
template <typename T> using RemoveReference = typename RemoveReferenceImpl <T>::result;

template <typename T> using AddConst = const T;

template <typename T> using AddLReference = T&;

template <typename T> using AddRReference = T&&;