//sfinae.h
#pragma once
#include <xtr1common>
#include <type_traits>
#include <functional>
#include <xutility>

namespace sfinae
{

  template <bool value>
  using if_t = std::enable_if_t<value>;



  template <bool value>
  using boolean = std::bool_constant<value>;
  using boolean_true = boolean<true>;
  using boolean_false = boolean<false>;



  template <typename T>
  using pure = std::remove_reference_t<std::remove_cv_t<T>>;



  template <typename T1, typename T2>
  using is_same = std::is_same<pure<T1>, pure<T2>>;

  template <typename T1, typename T2>
  constexpr bool is_same_v = is_same<pure<T1>, pure<T2>>::value;

  template <typename T1, typename T2>
  using if_same = if_t<is_same_v<T1, T2>>;

  template <typename T1, typename T2>
  using if_not_same = if_t<!is_same_v<T1, T2>>;



  template <typename T1, typename T2>
  using is_exact = std::is_same<T1, T2>;

  template <typename T1, typename T2>
  constexpr bool is_exact_v = is_exact<T1, T2>::value;

  template <typename T1, typename T2>
  using if_exact = if_t<is_exact_v<T1, T2>>;



  template <typename T>
  using is_simple = std::is_arithmetic<std::remove_reference_t<T>>;

  template <typename T>
  constexpr bool is_simple_v = is_simple<T>::value;

  template <typename T>
  using if_simple = if_t<is_simple_v<T>>;



  template <typename T, typename Return, typename... Args>
  using is_function = std::is_convertible<T, std::function<Return(Args...)>>;

  template <typename T, typename Return, typename... Args>
  constexpr bool is_function_v = is_function<T, Return, Args...>::value;

  template <typename T, typename Return, typename... Args>
  using if_function = if_t<is_function_v<T, Return, Args...>>;



  template <typename T, typename Arg>
  using is_unary_predicate = is_function<T, bool, const Arg&>;

  template <typename T, typename Arg>
  constexpr bool is_unary_predicate_v = is_unary_predicate<T, Arg>::value;

  template <typename T, typename Arg>
  using if_unary_predicate = if_t<is_unary_predicate_v<T, Arg>>;



  template <typename T, typename Arg>
  using is_binary_predicate = is_function<T, bool, const Arg&, const Arg&>;

  template <typename T, typename Arg>
  constexpr bool is_binary_predicate_v = is_binary_predicate<T, Arg>::value;

  template <typename T, typename Arg>
  using if_binary_predicate = if_t<is_binary_predicate_v<T, Arg>>;



  template<typename T, typename = void>
  struct has_value_type : std::false_type {};

  template<typename T>
  struct has_value_type<T, std::void_t<typename pure<T>::value_type>> : std::true_type {};

  template <typename T>
  constexpr bool has_value_type_v = has_value_type<T>::value;

  template <typename T>
  using if_has_value_type = if_t<has_value_type_v<T>>;



  template<typename T, typename = void>
  struct has_iterator : std::false_type {};

  template<typename T>
  struct has_iterator<T, std::void_t<typename pure<T>::iterator>> : std::true_type {};

  template <typename T>
  constexpr bool has_iterator_v = has_iterator<T>::value;

  template <typename T>
  using if_has_iterator = if_t<has_iterator_v<T>>;



  template<typename T, typename = void>
  struct has_const_iterator : std::false_type {};

  template<typename T>
  struct has_const_iterator<T, std::void_t<typename pure<T>::const_iterator>> : std::true_type {};

  template <typename T>
  constexpr bool has_const_iterator_v = has_const_iterator<T>::value;

  template <typename T>
  using if_has_const_iterator = if_t<has_const_iterator_v<T>>;



  template<typename T, typename = void>
  struct has_allocator_type : std::false_type {};

  template<typename T>
  struct has_allocator_type<T, std::void_t<typename pure<T>::allocator_type>> : std::true_type {};

  template <typename T>
  constexpr bool has_allocator_type_v = has_allocator_type<T>::value;

  template <typename T>
  using if_has_allocator_type = if_t<has_allocator_type_v<T>>;



  template<typename T, typename = void>
  struct has_key_type : std::false_type {};

  template<typename T>
  struct has_key_type<T, std::void_t<typename pure<T>::key_type>> : std::true_type {};

  template <typename T>
  constexpr bool has_key_type_v = has_key_type<T>::value;

  template <typename T>
  using if_has_key_type = if_t<has_key_type_v<T>>;



  template <typename T, typename TAG>
  using check_iterator_category = std::is_convertible<std::_Iter_cat_t<T>, TAG>;



  template <typename T>
  using is_iterator_input = check_iterator_category<T, std::bidirectional_iterator_tag>;

  template <typename T>
  constexpr bool is_iterator_input_v = is_iterator_input<T>::value;

  template <typename T>
  using if_iterator_input = if_t<is_iterator_input_v<T>>;



  template <typename T>
  using is_iterator_forward = check_iterator_category<T, std::bidirectional_iterator_tag>;

  template <typename T>
  constexpr bool is_iterator_forward_v = is_iterator_forward<T>::value;

  template <typename T>
  using if_iterator_forward = if_t<is_iterator_forward_v<T>>;



  template <typename T>
  using is_iterator_bidirectional = check_iterator_category<T, std::bidirectional_iterator_tag>;

  template <typename T>
  constexpr bool is_iterator_bidirectional_v = is_iterator_bidirectional<T>::value;

  template <typename T>
  using if_iterator_bidirectional = if_t<is_iterator_bidirectional_v<T>>;



  template <typename T>
  using is_iterator_random = check_iterator_category<T, std::random_access_iterator_tag>;

  template <typename T>
  constexpr bool is_iterator_random_v = is_iterator_random<T>::value;

  template <typename T>
  using if_iterator_random = if_t<is_iterator_random_v<T>>;



  template <typename T>
  using is_container = boolean<has_value_type_v<T> && has_iterator_v<T> && has_const_iterator_v<T>>;

  template<typename T>
  constexpr bool is_container_v = is_container<T>::value;

  template <typename T>
  using if_container = if_t<is_container_v<T>>;



  template <typename T>
  using is_container_dynamic = boolean<is_container_v<T> && has_allocator_type_v<T>>;

  template<typename T>
  constexpr bool is_container_dynamic_v = is_container_dynamic<T>::value;

  template <typename T>
  using if_container_dynamic = if_t<is_container_dynamic_v<T>>;



  template <typename T>
  using is_container_static = boolean<is_container_v<T> && !has_allocator_type_v<T>>;

  template<typename T>
  constexpr bool is_container_static_v = is_container_static<T>::value;

  template <typename T>
  using if_container_static = if_t<is_container_static_v<T>>;



  template <typename T>
  using is_container_linear = boolean<is_container_v<T> && !has_key_type_v<T>>;

  template<typename T>
  constexpr bool is_container_linear_v = is_container_linear<T>::value;

  template <typename T>
  using if_container_linear = if_t<is_container_linear_v<T>>;



  template <typename T>
  using is_container_tree = boolean<is_container_v<T> && has_key_type_v<T>>;

  template<typename T>
  constexpr bool is_container_tree_v = is_container_tree<T>::value;

  template <typename T>
  using if_container_tree = if_t<is_container_tree_v<T>>;



  template<typename T, typename = void>
  struct is_container_input : std::false_type {};

  template<typename T>
  struct is_container_input<T, std::void_t<typename pure<T>::iterator>> : boolean<is_container_v<T> && is_iterator_input_v<typename pure<T>::iterator>> {};

  template<typename T>
  constexpr bool is_container_input_v = is_container_input<T>::value;

  template <typename T>
  using if_container_input = if_t<is_container_input_v<T>>;



  template<typename T, typename = void>
  struct is_container_forward : std::false_type {};

  template<typename T>
  struct is_container_forward<T, std::void_t<typename pure<T>::iterator>> : boolean<is_iterator_forward_v<typename pure<T>::iterator>> {};

  template<typename T>
  constexpr bool is_container_forward_v = is_container_forward<T>::value;

  template <typename T>
  using if_container_forward = if_t<is_container_forward_v<T>>;



  template<typename T, typename = void>
  struct is_container_bidirectional : std::false_type {};

  template<typename T>
  struct is_container_bidirectional<T, std::void_t<typename pure<T>::iterator>> : boolean<is_iterator_bidirectional_v<typename pure<T>::iterator>> {};

  template<typename T>
  constexpr bool is_container_bidirectional_v = is_container_bidirectional<T>::value;

  template <typename T>
  using if_container_bidirectional = if_t<is_container_bidirectional_v<T>>;



  template<typename T, typename = void>
  struct is_container_random : std::false_type {};

  template<typename T>
  struct is_container_random<T, std::void_t<typename pure<T>::iterator>> : boolean<is_iterator_random_v<typename pure<T>::iterator>> {};

  template<typename T>
  constexpr bool is_container_random_v = is_container_random<T>::value;

  template <typename T>
  using if_container_random = if_t<is_container_random_v<T>>;

} //namespace sfinae