//container.h
#pragma once
#include "sfinae.h"
#include <initializer_list>
#include <vector>
#include <list>
#include <deque>
#include <random>

#pragma warning(push)
#pragma warning(disable : 4544)

template<typename T>
class Container;
template <typename T>
using Vector = Container<std::vector<T>>;
template <typename T>
using List = Container<std::list<T>>;
template <typename T>
using Deque = Container<std::deque<T>>;

template <typename T>
using if_container_dynamic_linear_bidirectional_pure = sfinae::if_t<
  sfinae::is_container_dynamic_v<T>       &&
  sfinae::is_container_linear_v<T>        &&
  sfinae::is_container_bidirectional_v<T> &&
  sfinae::is_exact_v<T, sfinae::pure<T>>
>;

template<typename STDContainer, typename = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
class Container
{
  using ThisContainer = sfinae::pure<STDContainer>;

public:

  using value_type = typename ThisContainer::value_type;
  using iterator = typename ThisContainer::iterator;
  using const_iterator = typename ThisContainer::const_iterator;
  using allocator_type = typename ThisContainer::allocator_type;
  using size_type = size_t;

  static const size_type MAX_SIZE = std::numeric_limits<size_type>::max();
  static const size_type NOT_FOUND = MAX_SIZE;

private:

  using ThisInit = std::initializer_list<value_type>;
  using ThisClass = Container<ThisContainer>;

  template<typename T>
  using if_another_container = sfinae::if_t<sfinae::is_container_v<T> && !sfinae::is_same_v<ThisContainer, T> && !sfinae::is_same_v<ThisClass, T> && !sfinae::is_same_v<ThisInit, T>>;
  template<typename T>
  using if_not_init = sfinae::if_not_same<ThisInit, T>;
  template<typename T>
  using if_not_init = sfinae::if_not_same<ThisInit, T>;
  template<typename T>
  using if_not_this = sfinae::if_not_same<ThisClass, T>;
  template<typename T>
  using if_not_value_type = sfinae::if_not_same<value_type, T>;
  template<typename T>
  using if_container = sfinae::if_container<T>;
  template<typename T>
  using is_container = sfinae::is_container<T>;
  template<typename T>
  using if_container_value = sfinae::if_t<sfinae::is_container_v<T> || sfinae::is_same_v<value_type, T>>;
  template<typename T>
  using if_container_predicate1_value = sfinae::if_t<sfinae::is_container_v<T> || sfinae::is_unary_predicate_v<T, value_type> || sfinae::is_same_v<value_type, T>>;
  template<typename T>
  using if_predicate2 = sfinae::if_t<sfinae::is_binary_predicate_v<T, value_type>>;
  template<typename T>
  using is_predicate1 = sfinae::is_unary_predicate<T, value_type>;
  template<typename T>
  using is_value_type = sfinae::is_same<value_type, T>;
  template<typename T>
  using is_this_class = sfinae::is_same<ThisClass, T>;
  template<typename T>
  using is_this_container = sfinae::is_same<ThisContainer, T>;
  template<typename T>
  using is_this_init = sfinae::is_same<ThisInit, T>;
  using Vector_size = Container<std::vector<size_t>>;
  using list_value = std::list<value_type>;
  using vector_value = std::vector<value_type>;
  using deque_value = std::deque<value_type>;
  using boolean_true = sfinae::boolean_true;
  using boolean_false = sfinae::boolean_false;

public:

  template<typename T, typename = if_another_container<T>>
  Container(T&&);
  Container() = default;
  Container(const ThisInit&);
  Container(const ThisContainer&);
  Container(ThisContainer&&);
  Container(const ThisClass&);
  Container(ThisClass&&);

  template<typename T, typename = if_container<T>>
  Container& operator=(T&&);
  Container& operator=(const ThisClass&);
  Container& operator=(const ThisInit&);

  template<typename T, typename = if_container_value<T>>
  Container& operator+=(T&&);
  Container& operator+=(const ThisInit&);

  template<typename T, typename = if_container_value<T>>
  Container operator+(T&&) const;

  template<typename T, typename = if_container_value<T>>
  bool operator==(T&&) const;

  template<typename T, typename = if_container_value<T>>
  bool operator!=(T&&) const;

  value_type& operator[](size_t index);
  const value_type& operator[](size_t index) const;

  operator ThisContainer() const;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
  const_iterator begin() const;
  const_iterator end() const;
  constexpr size_t size() const;
  constexpr bool empty() const;

  template<typename T, typename = if_container_value<T>>
  void add(T&&);
  void add(const ThisInit&);

  template<typename T, typename = if_container_value<T>>
  void insert(size_t, T&&);
  void insert(size_t, const ThisInit&);

  template<typename T, typename = if_container_predicate1_value<T>>
  void remove(T&&);
  void remove(const ThisInit&);

  void erase(size_t, size_t = 1);

  template<typename T, typename = if_container_predicate1_value<T>>
  size_t find(T&&) const;
  size_t find(const ThisInit&) const;

  template<typename T, typename = if_container_predicate1_value<T>>
  Vector_size findAll(T&&) const;
  Vector_size findAll(const ThisInit&) const;

  template<typename T1, typename T2, typename = if_container_predicate1_value<T1>, typename = if_container_value<T2>>
  void replace(T1&&, T2&&);
  template<typename T, typename = if_container_value<T>>
  void replace(const ThisInit&, T&&);
  template<typename T, typename = if_container_predicate1_value<T>>
  void replace(T&&, const ThisInit&);
  void replace(const ThisInit&, const ThisInit&);

  template<typename T, typename = if_predicate2<T>>
  void sort(T&&);
  void sort();

  template<typename T, typename = if_predicate2<T>>
  bool isSorted(T&&) const;
  bool isSorted() const;

  template<typename T, typename = if_predicate2<T>>
  void unique(T&&);
  void unique();

  void shuffle();

  void reverse();

  Container sub(size_t, size_t) const;

  decltype(auto) toVector() const;
  decltype(auto) toVector(size_t, size_t) const;
  decltype(auto) toList() const;
  decltype(auto) toList(size_t, size_t) const;
  decltype(auto) toDeque() const;
  decltype(auto) toDeque(size_t, size_t) const;

  void rotateLeft(size_t);
  void rotateRight(size_t);

  template<typename T, typename = if_container_value<T>>
  void merge(T&&);
  void merge(const ThisInit&);
  template<typename T1, typename T2, typename = if_container_value<T1>, typename = if_predicate2<T2>>
  void merge(T1&&, T2&&);
  template<typename T, typename = if_predicate2<T>>
  void merge(const ThisInit&, T&&);

private:

  template<typename T>
  static void assign_helper(ThisContainer&, T&&);
  template<typename T> //this class
  static void assign_helper2(ThisContainer&, T&&, boolean_true);
  template<typename T> //this class
  static void assign_helper2(ThisContainer&, T&&, boolean_false);
  template<typename T> //this container
  static void assign_helper3(ThisContainer&, T&&, boolean_true);
  template<typename T> //this container
  static void assign_helper3(ThisContainer&, T&&, boolean_false);
  template<typename T> //this init
  static void assign_helper4(ThisContainer&, T&&, boolean_true);
  template<typename T> //any container
  static void assign_helper4(ThisContainer&, T&&, boolean_false);

  template<typename T>
  static bool equal_helper(const ThisContainer&, T&&);
  template<typename T> //this class
  static bool equal_helper2(const ThisContainer&, T&&, boolean_true);
  template<typename T> //this class
  static bool equal_helper2(const ThisContainer&, T&&, boolean_false);
  template<typename T> //this container
  static bool equal_helper3(const ThisContainer&, T&&, boolean_true);
  template<typename T> //this container
  static bool equal_helper3(const ThisContainer&, T&&, boolean_false);
  template<typename T> //value_type
  static bool equal_helper4(const ThisContainer&, T&&, boolean_true);
  template<typename T> //any container
  static bool equal_helper4(const ThisContainer&, T&&, boolean_false);

  template<typename T>
  static iterator insert_helper(ThisContainer&, const_iterator, T&&);
  template<typename T> //container
  static iterator insert_helper2(ThisContainer&, const_iterator, T&&, boolean_true);
  template<typename T> //value_type
  static iterator insert_helper2(ThisContainer&, const_iterator, T&&, boolean_false);

  template<typename T>
  static void find_helper(size_t&, const ThisContainer&, T&&);
  template<typename T>
  static void find_helper(Vector_size&, const ThisContainer&, T&&);
  template<typename T>
  static const_iterator find_helper2(const_iterator, const_iterator, T&&);
  template<typename T> //value_type
  static const_iterator find_helper3(const_iterator, const_iterator, T&&, boolean_true);
  template<typename T> //value_type
  static const_iterator find_helper3(const_iterator, const_iterator, T&&, boolean_false);
  template<typename T> //predicate1
  static const_iterator find_helper4(const_iterator, const_iterator, T&&, boolean_true);
  template<typename T> //container
  static const_iterator find_helper4(const_iterator, const_iterator, T&&, boolean_false);

  template<typename T1, typename T2>
  static void remove_helper(T1&, T2&&);
  template<typename T1, typename T2> //value_type
  static void remove_helper2(T1&, T2&&, boolean_true);
  template<typename T> //value_type
  static void remove_helper2(list_value&, T&&, boolean_true);
  template<typename T1, typename T2> //value_type
  static void remove_helper2(T1&, T2&&, boolean_false);
  template<typename T1, typename T2> //predicate1
  static void remove_helper3(T1&, T2&&, boolean_true);
  template<typename T> //predicate1
  static void remove_helper3(list_value&, T&&, boolean_true);
  template<typename T1, typename T2> //container
  static void remove_helper3(T1&, T2&&, boolean_false);

  static void erase_helper(ThisContainer&, size_t, size_t);

  template<typename T1, typename T2>
  static void replace_helper(ThisContainer&, T1&&, T2&&);

  template<typename T, typename Predicate>
  static void sort_helper(T&&, Predicate&&);
  template<typename Predicate>
  static void sort_helper(list_value&, Predicate&&);

  template<typename Predicate>
  static bool is_sorted_helper(const ThisContainer&, Predicate&&);

  template<typename T, typename Predicate>
  static void unique_helper(T&&, Predicate&&);
  template<typename Predicate>
  static void unique_helper(list_value&, Predicate&&);

  template<typename T>
  static void shuffle_helper(T&&);
  static void shuffle_helper(list_value&);

  template<typename T>
  static void reverse_helper(T&&);
  static void reverse_helper(list_value&);

  template<typename T>
  static Container<T> sub_helper(const ThisContainer&);
  template<typename T>
  static Container<T> sub_helper(const ThisContainer&, size_t, size_t);

  template<typename T, typename Predicate>
  static void merge_helper(ThisContainer&, T&&, Predicate&&);
  template<typename T, typename Predicate> //value_type
  static void merge_helper2(ThisContainer&, T&&, Predicate&&, boolean_true);
  template<typename T, typename Predicate> //any container
  static void merge_helper2(ThisContainer&, T&&, Predicate&&, boolean_false);
  template<typename T, typename Predicate>
  static void merge_helper3(ThisContainer&, T&&, T&&, Predicate&&);

  template<typename T>
  static constexpr bool empty_helper(T&&);
  template<typename T> //container
  static constexpr bool empty_helper2(T&&, boolean_true);
  template<typename T> //not container
  static constexpr bool empty_helper2(T&&, boolean_false);

  template<typename T>
  static constexpr size_t size_helper(T&&);
  template<typename T> //container
  static constexpr size_t size_helper2(T&&, boolean_true);
  template<typename T> //not container
  static constexpr size_t size_helper2(T&&, boolean_false);

private:

  ThisContainer m_items;
};

///////////////////////////implementation///////////////////////////////

//CONSTRUCTORS

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_another_container<T>>
Container<STDContainer, U>::Container(T&& items)
  : m_items(items.begin(), items.end())
{}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
Container<STDContainer, U>::Container(const ThisInit& items)
  : m_items(items)
{}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
Container<STDContainer, U>::Container(const ThisContainer& items)
  : m_items(items)
{}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
Container<STDContainer, U>::Container(ThisContainer&& items)
  : m_items(std::move(items))
{}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
Container<STDContainer, U>::Container(const ThisClass& items)
  : m_items(items.m_items)
{}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
Container<STDContainer, U>::Container(ThisClass&& items)
  : m_items(std::move(items.m_items))
{}

//OPERATOR =

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_container<T>>
Container<STDContainer, U>& Container<STDContainer, U>::operator=(T&& items)
{
  assign_helper(m_items, std::forward<T>(items));
  return *this;
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
Container<STDContainer, U>& Container<STDContainer, U>::operator=(const ThisClass& items)
{
  assign_helper(m_items, items);
  return *this;
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
Container<STDContainer, U>& Container<STDContainer, U>::operator=(const ThisInit& items)
{
  assign_helper(m_items, items);
  return *this;
}

//OPERATOR +=

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_container_value<T>>
Container<STDContainer, U>& Container<STDContainer, U>::operator+=(T&& items)
{
  add(std::forward<T>(items));
  return *this;
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
Container<STDContainer, U>& Container<STDContainer, U>::operator+=(const ThisInit& items)
{
  add(items);
  return *this;
}

//OPERATOR +

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_container_value<T>>
Container<STDContainer, U> Container<STDContainer, U>::operator+(T&& items) const
{
  Container<STDContainer> result(m_items);
  result.add(std::forward<T>(items));
  return result;
}

//OPERATOR ==

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_container_value<T>>
bool Container<STDContainer, U>::operator==(T&& items) const
{
  return equal_helper(m_items, items);
}

//OPERATOR !=

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_container_value<T>>
bool Container<STDContainer, U>::operator!=(T&& items) const
{
  return !operator==(items);
}

//OPERATOR []

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
typename Container<STDContainer, U>::value_type& Container<STDContainer, U>::operator[](size_t index)
{
  return *std::next(begin(), index);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
const typename Container<STDContainer, U>::value_type& Container<STDContainer, U>::operator[](size_t index) const
{
  return *std::next(begin(), index);
}

//OPERATOR CONTAINER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
Container<STDContainer, U>::operator ThisContainer() const
{
  return m_items;
}

//ITERATORS

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
inline typename Container<STDContainer, U>::iterator Container<STDContainer, U>::begin()
{
  return m_items.begin();
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
inline typename Container<STDContainer, U>::iterator Container<STDContainer, U>::end()
{
  return m_items.end();
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
inline typename Container<STDContainer, U>::const_iterator Container<STDContainer, U>::cbegin() const
{
  return m_items.cbegin();
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
inline typename Container<STDContainer, U>::const_iterator Container<STDContainer, U>::cend() const
{
  return m_items.cend();
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
inline typename Container<STDContainer, U>::const_iterator Container<STDContainer, U>::begin() const
{
  return m_items.begin();
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
inline typename Container<STDContainer, U>::const_iterator Container<STDContainer, U>::end() const
{
  return m_items.end();
}

//SIZE

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
inline constexpr size_t Container<STDContainer, U>::size() const
{
  return m_items.size();
}

//EMPTY

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
inline constexpr bool Container<STDContainer, U>::empty() const
{
  return m_items.empty();
}

//ADD

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_container_value<T>>
void Container<STDContainer, U>::add(T&& items)
{
  insert_helper(m_items, end(), std::forward<T>(items));
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::add(const ThisInit& items)
{
  insert_helper(m_items, end(), items);
}

//INSERT

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_container_value<T>>
void Container<STDContainer, U>::insert(size_t index, T&& items)
{
  if (index < size())
  {
    insert_helper(m_items, std::next(begin(), index), std::forward<T>(items));
  }
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::insert(size_t index, const ThisInit& items)
{
  if (index < size())
  {
    insert_helper(m_items, std::next(begin(), index), items);
  }
}

//REMOVE

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_container_predicate1_value<T>>
void Container<STDContainer, U>::remove(T&& items)
{
  remove_helper(m_items, items);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::remove(const ThisInit& items)
{
  remove_helper(m_items, items);
}

//ERASE

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::erase(size_t index, size_t size)
{
  erase_helper(m_items, index, size);
}

//FIND

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_container_predicate1_value<T>>
size_t Container<STDContainer, U>::find(T&& items) const
{
  size_t result;
  find_helper(result, m_items, std::forward<T>(items));
  return result;
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
size_t Container<STDContainer, U>::find(const ThisInit& items) const
{
  size_t result;
  find_helper(result, m_items, items);
  return result;
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_container_predicate1_value<T>>
Container<std::vector<size_t>> Container<STDContainer, U>::findAll(T&& items) const
{
  Vector_size results;
  find_helper(results, m_items, std::forward<T>(items));
  return results;
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
Container<std::vector<size_t>> Container<STDContainer, U>::findAll(const ThisInit& items) const
{
  Vector_size results;
  find_helper(results, m_items, items);
  return results;
}

//REPLACE

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T1, typename T2, typename = if_container_predicate1_value<T1>, typename = if_container_value<T2>>
void Container<STDContainer, U>::replace(T1&& oldItems, T2&& newItems)
{
  replace_helper(m_items, oldItems, newItems);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_container_value<T>>
void Container<STDContainer, U>::replace(const ThisInit& oldItems, T&& newItems)
{
  replace_helper(m_items, oldItems, newItems);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_container_predicate1_value<T>>
void Container<STDContainer, U>::replace(T&& oldItems, const ThisInit& newItems)
{
  replace_helper(m_items, oldItems, newItems);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::replace(const ThisInit& oldItems, const ThisInit& newItems)
{
  replace_helper(m_items, oldItems, newItems);
}

//SORT

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_predicate2<T>>
void Container<STDContainer, U>::sort(T&& predicate)
{
  sort_helper(m_items, predicate);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::sort()
{
  sort_helper(m_items, std::less<>());
}

//IS SORTED

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_predicate2<T>>
bool Container<STDContainer, U>::isSorted(T&& predicate) const
{
  return is_sorted_helper(m_items, predicate);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
bool Container<STDContainer, U>::isSorted() const
{
  return is_sorted_helper(m_items, std::less<>());
}

//UNIQUE

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_predicate2<T>>
void Container<STDContainer, U>::unique(T&& predicate)
{
  unique_helper(m_items, predicate);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::unique()
{
  unique_helper(m_items, std::equal_to<>());
}

//SHUFFLE

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::shuffle()
{
  shuffle_helper(m_items);
}

//REVERSE

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::reverse()
{
  reverse_helper(m_items);
}

//SUB

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
Container<STDContainer, U> Container<STDContainer, U>::sub(size_t index, size_t size) const
{
  return sub_helper<STDContainer>(m_items, index, size);
}

//TO CONTAINERS

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
decltype(auto) Container<STDContainer, U>::toVector() const
{
  return sub_helper<vector_value>(m_items);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
decltype(auto) Container<STDContainer, U>::toVector(size_t index, size_t size) const
{
  return sub_helper<vector_value>(m_items, index, size);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
decltype(auto) Container<STDContainer, U>::toList() const
{
  return sub_helper<list_value>(m_items);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
decltype(auto) Container<STDContainer, U>::toList(size_t index, size_t size) const
{
  return sub_helper<list_value>(m_items, index, size);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
decltype(auto) Container<STDContainer, U>::toDeque() const
{
  return sub_helper<deque_value>(m_items);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
decltype(auto) Container<STDContainer, U>::toDeque(size_t index, size_t size) const
{
  return sub_helper<deque_value>(m_items, index, size);
}

//ROTATE

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::rotateLeft(size_t count)
{
  std::rotate(m_items.rbegin(), std::next(m_items.rbegin(), count %= size()), m_items.rend());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::rotateRight(size_t count)
{
  std::rotate(m_items.begin(), std::next(m_items.begin(), count %= size()), m_items.end());
}

//MERGE

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_container_value<T>>
void Container<STDContainer, U>::merge(T&& items)
{
  merge_helper(m_items, items, std::less<>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::merge(const ThisInit& items)
{
  merge_helper(m_items, items, std::less<>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T1, typename T2, typename = if_container_value<T1>, typename = if_predicate2<T2>>
void Container<STDContainer, U>::merge(T1&& items, T2&& predicate)
{
  merge_helper(m_items, items, predicate);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename = if_predicate2<T>>
void Container<STDContainer, U>::merge(const ThisInit& items, T&& predicate)
{
  merge_helper(m_items, items, predicate);
}


///////////////////////////helpers///////////////////////////////

//ASSIGN HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
void Container<STDContainer, U>::assign_helper(ThisContainer& container, T&& items)
{
  assign_helper2(container, std::forward<T>(items), is_this_class<T>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //this class
void Container<STDContainer, U>::assign_helper2(ThisContainer& container, T&& items, boolean_true)
{
  container = std::forward<T>(items).m_items;
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //this class
void Container<STDContainer, U>::assign_helper2(ThisContainer& container, T&& items, boolean_false)
{
  assign_helper3(container, std::forward<T>(items), is_this_container<T>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //this container
void Container<STDContainer, U>::assign_helper3(ThisContainer& container, T&& items, boolean_true)
{
  container = std::forward<T>(items);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //this container
void Container<STDContainer, U>::assign_helper3(ThisContainer& container, T&& items, boolean_false)
{
  assign_helper4(container, std::forward<T>(items), is_this_init<T>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //this init
void Container<STDContainer, U>::assign_helper4(ThisContainer& container, T&& items, boolean_true)
{
  container.assign(std::forward<T>(items));
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //any container
void Container<STDContainer, U>::assign_helper4(ThisContainer& container, T&& items, boolean_false)
{
  container.assign(items.begin(), items.end());
}

//EQUAL HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
bool Container<STDContainer, U>::equal_helper(const ThisContainer& container, T&& items)
{
  return equal_helper2(container, items, is_this_class<T>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //this class
bool Container<STDContainer, U>::equal_helper2(const ThisContainer& container, T&& items, boolean_true)
{
  return container == items.m_items;
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //this class
bool Container<STDContainer, U>::equal_helper2(const ThisContainer& container, T&& items, boolean_false)
{
  return equal_helper3(container, std::forward<T>(items), is_this_container<T>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //this container
bool Container<STDContainer, U>::equal_helper3(const ThisContainer& container, T&& items, boolean_true)
{
  return container == items;
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //this container
bool Container<STDContainer, U>::equal_helper3(const ThisContainer& container, T&& items, boolean_false)
{
  return equal_helper4(container, std::forward<T>(items), is_value_type<T>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //value_type
bool Container<STDContainer, U>::equal_helper4(const ThisContainer& container, T&& items, boolean_true)
{
  return !container.empty() && std::next(container.begin(), 1) == container.end() && *container.begin() == items;
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //any container
bool Container<STDContainer, U>::equal_helper4(const ThisContainer& container, T&& items, boolean_false)
{
  return std::equal(container.begin(), container.end(), items.begin(), items.end());
}

//INSERT HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
typename Container<STDContainer, U>::iterator Container<STDContainer, U>::insert_helper(ThisContainer& container, const_iterator it, T&& items)
{
  return insert_helper2(container, it, std::forward<T>(items), is_container<T>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
typename Container<STDContainer, U>::iterator Container<STDContainer, U>::insert_helper2(ThisContainer& container, const_iterator it, T&& items, boolean_true)
{
  return container.insert(it, items.begin(), items.end());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
typename Container<STDContainer, U>::iterator Container<STDContainer, U>::insert_helper2(ThisContainer& container, const_iterator it, T&& items, boolean_false)
{
  return container.insert(it, std::forward<T>(items));
}

//FIND HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
void Container<STDContainer, U>::find_helper(size_t& result, const ThisContainer& ñontainer, T&& items)
{
  auto it = find_helper2(ñontainer.cbegin(), ñontainer.cend(), items);
  result = it != ñontainer.cend() ? std::distance(ñontainer.cbegin(), it) : NOT_FOUND;
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
void Container<STDContainer, U>::find_helper(Vector_size& results, const ThisContainer& container, T&& items)
{
  if (!empty_helper(items))
  {
    size_t index = 0;
    size_t sz = size_helper(items);
    auto prev = container.cbegin();
    auto end = container.cend();
    auto it = find_helper2(prev, end, items);
    while (it != end)
    {
      results.add(index += std::distance(prev, it));
      prev = std::next(it, sz);
      it = find_helper2(prev, end, items);
      index += sz;
    }
  }
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
typename Container<STDContainer, U>::const_iterator Container<STDContainer, U>::find_helper2(const_iterator begin, const_iterator end, T&& items)
{
  return find_helper3(begin, end, std::forward<T>(items), is_value_type<T>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //value_type
typename Container<STDContainer, U>::const_iterator Container<STDContainer, U>::find_helper3(const_iterator begin, const_iterator end, T&& item, boolean_true)
{
  return std::find(begin, end, std::forward<T>(item));
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //value_type
typename Container<STDContainer, U>::const_iterator Container<STDContainer, U>::find_helper3(const_iterator begin, const_iterator end, T&& items, boolean_false)
{
  return find_helper4(begin, end, std::forward<T>(items), is_predicate1<T>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //predicate1
typename Container<STDContainer, U>::const_iterator Container<STDContainer, U>::find_helper4(const_iterator begin, const_iterator end, T&& predicate, boolean_true)
{
  return std::find_if(begin, end, std::forward<T>(predicate));
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //container
typename Container<STDContainer, U>::const_iterator Container<STDContainer, U>::find_helper4(const_iterator begin, const_iterator end, T&& items, boolean_false)
{
  return empty_helper(items) ? end : std::search(begin, end, items.begin(), items.end());
}

//REMOVE HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T1, typename T2>
void Container<STDContainer, U>::remove_helper(T1& container, T2&& items)
{
  remove_helper2(container, items, is_value_type<T2>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T1, typename T2> //value_type
void Container<STDContainer, U>::remove_helper2(T1& container, T2&& items, boolean_true)
{
  container.erase(std::remove(container.begin(), container.end(), items), container.end());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //value_type
void Container<STDContainer, U>::remove_helper2(list_value& container, T&& items, boolean_true)
{
  container.remove(items);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T1, typename T2> //value_type
void Container<STDContainer, U>::remove_helper2(T1& container, T2&& items, boolean_false)
{
  remove_helper3(container, items, is_predicate1<T2>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T1, typename T2> //predicate1
void Container<STDContainer, U>::remove_helper3(T1& container, T2&& predicate, boolean_true)
{
  container.erase(std::remove_if(container.begin(), container.end(), predicate), container.end());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //predicate1
void Container<STDContainer, U>::remove_helper3(list_value& container, T&& predicate, boolean_true)
{
  container.remove_if(predicate);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T1, typename T2> //container
void Container<STDContainer, U>::remove_helper3(T1& container, T2&& items, boolean_false)
{
  size_t size = size_helper(items);
  auto it = find_helper2(container.begin(), container.end(), items);
  while (it != container.end())
  {
    it = container.erase(it, std::next(it, size));
    it = find_helper2(it, container.end(), items);
  }
}

//ERASE HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::erase_helper(ThisContainer& container, size_t index, size_t size)
{
  if (size && index + size <= container.size())
  {
    auto it = std::next(container.begin(), index);
    container.erase(it, std::next(it, size));
  }
}

//REPLACE HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T1, typename T2>
void Container<STDContainer, U>::replace_helper(ThisContainer& container, T1&& oldItems, T2&& newItems)
{
  Vector_size results;
  find_helper(results, container, oldItems);
  if (!results.empty())
  {
    remove_helper(container, oldItems);
    if (!empty_helper(newItems))
    {
      size_t size = results.size();
      size_t deltaSize = size_helper(newItems) - size_helper(oldItems);
      size_t i = 0;
      //TODO reserve capacity
      auto it = insert_helper(container, std::next(container.begin(), results[0]), newItems);
      while (++i < size)
      {
        it = std::next(it, results[i] - results[i - 1] + deltaSize);
        it = insert_helper(container, it, newItems);
      }
    }
  }
}

//SORT HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename Predicate>
void Container<STDContainer, U>::sort_helper(T&& container, Predicate&& predicate)
{
  std::sort(container.begin(), container.end(), predicate);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename Predicate>
void Container<STDContainer, U>::sort_helper(list_value& container, Predicate&& predicate)
{
  container.sort(predicate);
}

//IS SORTED HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename Predicate>
bool Container<STDContainer, U>::is_sorted_helper(const ThisContainer& container, Predicate&& predicate)
{
  return std::is_sorted(container.begin(), container.end(), predicate);
}

//UNIQUE HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename Predicate>
void Container<STDContainer, U>::unique_helper(T&& container, Predicate&& predicate)
{
  container.erase(std::unique(container.begin(), container.end(), predicate), container.end());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename Predicate>
void Container<STDContainer, U>::unique_helper(list_value& container, Predicate&& predicate)
{
  container.unique(predicate);
}

//SHUFFLE HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
void Container<STDContainer, U>::shuffle_helper(T&& container)
{
  std::shuffle(container.begin(), container.end(), std::mt19937(std::random_device()()));
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::shuffle_helper(list_value& container)
{
  std::vector<std::reference_wrapper<value_type>> temp(container.begin(), container.end());
  shuffle_helper(temp);
  container = list_value(temp.begin(), temp.end());
}

//REVERSE HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
void Container<STDContainer, U>::reverse_helper(T&& container)
{
  std::reverse(container.begin(), container.end());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
void Container<STDContainer, U>::reverse_helper(list_value& container)
{
  container.reverse();
}

//SUB HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
Container<T> Container<STDContainer, U>::sub_helper(const ThisContainer& container)
{
  return Container<T>(T(container.begin(), container.end()));
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
Container<T> Container<STDContainer, U>::sub_helper(const ThisContainer& container, size_t index, size_t size)
{
  if (size && index + size <= container.size())
  {
    auto start = std::next(container.begin(), index);
    return Container<T>(T(start, std::next(start, size)));
  }
  return Container<T>();
}

//MERGE HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename Predicate>
void Container<STDContainer, U>::merge_helper(ThisContainer& container, T&& items, Predicate&& predicate)
{
  return merge_helper2(container, items, predicate, is_value_type<T>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename Predicate> //this class
void Container<STDContainer, U>::merge_helper2(ThisContainer& container, T&& items, Predicate&& predicate, boolean_true)
{
  merge_helper3(container, &items, &items + 1, predicate);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename Predicate> //any container
void Container<STDContainer, U>::merge_helper2(ThisContainer& container, T&& items, Predicate&& predicate, boolean_false)
{
  merge_helper3(container, items.begin(), items.end(), predicate);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T, typename Predicate>
void Container<STDContainer, U>::merge_helper3(ThisContainer& container, T&& begin, T&& end, Predicate&& predicate)
{
  ThisContainer temp;
  std::merge(container.begin(), container.end(), begin, end, std::back_inserter(temp), predicate);
  container = std::move(temp);
}

//EMPTY HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
constexpr bool Container<STDContainer, U>::empty_helper(T&& items)
{
  return empty_helper2(items, is_container<T>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //container
constexpr bool Container<STDContainer, U>::empty_helper2(T&& items, boolean_true)
{
  return std::empty(items);
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //container
constexpr bool Container<STDContainer, U>::empty_helper2(T&& items, boolean_false)
{
  return false;
}

//SIZE HELPER

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T>
constexpr size_t Container<STDContainer, U>::size_helper(T&& items)
{
  return size_helper2(items, is_container<T>());
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //container
constexpr size_t Container<STDContainer, U>::size_helper2(T&& items, boolean_true)
{
  return items.size();
}

template<typename STDContainer, typename U = if_container_dynamic_linear_bidirectional_pure<STDContainer>>
template<typename T> //not container
constexpr size_t Container<STDContainer, U>::size_helper2(T&& items, boolean_false)
{
  return 1;
}

#pragma warning(pop)