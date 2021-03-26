#pragma once
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <functional>
#include "Utils.h"

using STDString = std::string;
template<typename T>
using STDList = std::list<T>;
template<typename T>
using STDVector = std::vector<T>;
template<typename T>
using STDInit = std::initializer_list<T>;

template<typename STDContainer>
class Container;
template<typename T>
using List = Container<STDList<T>>;
template<typename T>
using Vector = Container<STDVector<T>>;


template<typename STDContainer>
class Container
{
  using InnerType = typename STDContainer::value_type;

protected:

  using STDListT   = STDList  <InnerType>;
  using STDVectorT = STDVector<InnerType>;
  using STDInitT   = STDInit  <InnerType>;
  using ThisClass  = Container<STDContainer>;
  using Iterator   = typename STDContainer::iterator;
  using Func       = std::function<void(Iterator, Iterator)>;

public:

  Container              ();
  //template<typename T>
  //Container              (const T & items);
  Container              (const STDInitT & items);
  
  template<typename T>
  void  add              (const T & items);
  void  add              (const STDInitT & items);
  template<typename T>
  void  insert           (const T & items, int index);
  template<typename T1, typename T2>
  void  replace          (const T1 & oldItems, const T2 & newItems);
  template<typename T>
  void  replace          (int index, int count, const T  & newItem);

  void  removeByValue    (const InnerType  & item,      int index = 0);
  void  removeByValue    (const InnerType  & item,      int index, int count);
  void  removeByValueAll (const InnerType  & item,      int index = 0);
  void  removeByValueAll (const InnerType  & item,      int index, int count);
  void  remove           (int                index,     int count = 1);
        
  int   size             ();
  void  clear            ();
  int   find             (const InnerType item,        int index = 0);
  Vector<int> findAll    (const InnerType item);
  void  reverse          (int             index = 0);
  void  reverse          (int             index,       int count);
  void  sort             (bool            ascending = true);

  Container sub          (int index);
  Container sub          (int index, int count);

  //todo 
  //operator+
  // swap first-second

  InnerType&   operator[](int index);
  bool operator==(const ThisClass &container);
  bool operator!=(const ThisClass &container);

protected:

  static void rangeDoHelper(STDContainer &container, int index, int count, Func func);
  template<typename AnySTDContainer>
  static void insertHelper(const AnySTDContainer &container, STDContainer &itemsDst, int index);
  static void insertHelper(const InnerType &item, STDContainer &itemsDst, int index);
  template<typename AnySTDContainer>
  static void subHelper(const AnySTDContainer &container, STDContainer &itemsDst, int index, int count);
  static void reverseHelper(STDContainer &container, int index, int count);
  static void removeHelper(STDContainer &container, int index, int count);
  static void removeByValueFirstHelper(STDContainer & container, const InnerType & item, int index, int count);
  static void removeByValueAllHelper(STDContainer & container, const InnerType & item, int index, int count);
  static void sortHelper(STDListT &container, bool ascending = true);
  static void sortHelper(STDVectorT &container, bool ascending = true);
  static void findAllHelper(Vector<int> & indexes, STDContainer & container, const InnerType & item);
  static void replaceHelper(STDContainer &container, const InnerType & oldItem, const InnerType & newItem);
  template<typename AnySTDContainer>
  static void replaceHelper(STDContainer &container, const InnerType & oldItem, const AnySTDContainer & anyContainer);
  template<typename T>
  static const T& getSTL(const T&);
  static const STDInitT& getSTL(const STDInitT&);
  static const STDContainer& getSTL<ThisClass>(const ThisClass&);

protected:

  STDContainer m_items;

};

////////////////static impementation////////////////

template<typename STDContainer>
void Container<STDContainer>::rangeDoHelper(STDContainer & items, int index, int count, Func func)
{
  if (utils::isInRange(0, index, int(items.size()) - 1) && count > 0)
  {
    func(std::next(items.begin(), index),std::next(items.begin(),utils::min(int(items.size()),index + count)));
  }
}

template<typename STDContainer>
void Container<STDContainer>::insertHelper(const InnerType &item, STDContainer &itemsDst, int index)
{
  if ( utils::isInRange(0, index, int(itemsDst.size())) )
  {
    itemsDst.insert(std::next(itemsDst.begin(), index), item);
  }
}

template<typename STDContainer>
template<typename AnySTDContainer>
void Container<STDContainer>::insertHelper(const AnySTDContainer &items, STDContainer &itemsDst, int index)
{
  if (utils::isInRange(0, index, int(itemsDst.size())))
  {
    itemsDst.insert(std::next(itemsDst.begin(), index), items.begin(), items.end());
  }
}

template<typename STDContainer>
void Container<STDContainer>::reverseHelper(STDContainer & container, int index, int count)
{
  rangeDoHelper(container, index, count, [](Iterator & first, Iterator & last)
  {
    std::reverse(first, last);
  });
}

template<typename STDContainer>
void Container<STDContainer>::removeHelper(STDContainer & container, int index, int count)
{
  rangeDoHelper(container, index, count, [&container](Iterator & first, Iterator & last)
  {
    container.erase(first, last);
  });
}

template<typename STDContainer>
void Container<STDContainer>::removeByValueFirstHelper(STDContainer & container, const InnerType & item, int index, int count)
{
  rangeDoHelper(container, index, count, [&container, &item](Iterator & first, Iterator & last)
  {
    container.erase(std::find(first, last, item));
  });
}

template<typename STDContainer>
void Container<STDContainer>::removeByValueAllHelper(STDContainer & container, const InnerType & item, int index, int count)
{
  rangeDoHelper(container, index, count, [&container, &item](Iterator & first, Iterator & last)
  {
    container.erase(std::remove(first, last, item), last);
  });
}

template<typename STDContainer>
void Container<STDContainer>::sortHelper(STDListT & container, bool ascending /* = true */)
{
  container.sort(ascending ? less<InnerType>() : greater<InnerType>());
}

template<typename STDContainer>
void Container<STDContainer>::sortHelper(STDVectorT & container, bool ascending /* = true */)
{
  if (ascending)
  {
    std::sort(container.begin(), container.end());
  }
  else
  {
    std::sort(container.begin(), container.end(), greater<>());
  }
}

template<typename STDContainer>
void Container<STDContainer>::findAllHelper(Vector<int> & indexes, STDContainer & container, const InnerType & item)
{
  int index = 0;
  for (auto &it : container)
  {
    if (it == item)
    {
      indexes.add(index);
    }
    index++;
  }
}

template<typename STDContainer>
template<typename AnySTDContainer>
 void Container<STDContainer>::subHelper(const AnySTDContainer &items, STDContainer & itemsDst, int index, int count)
{
  rangeDoHelper(items, index, count, [&itemsDst](Iterator & first, Iterator & last)
  {
    itemsDst.assign(first, last);
  });
}

template<typename STDContainer>
void Container<STDContainer>::replaceHelper(STDContainer &container, const InnerType &oldItem, const InnerType &newItem)
{
  std::replace(container.begin(), container.end(), oldItem, newItem);
}

template<typename STDContainer>
template<typename AnySTDContainer>
void Container<STDContainer>::replaceHelper(STDContainer & container, const InnerType &oldItem, const AnySTDContainer & anyContainer)
{
  Vector<int> indexes;
  findAllHelper(indexes, container, oldItem);
  removeByValueAllHelper(container, oldItem, 0, container.size());
  int shift = 0;
  int size = anyContainer.size() - 1;
  for (int i = 0; i < indexes.size(); i++)
  {
    insertHelper(anyContainer, container, indexes[i] + shift);
    shift += size;
  }
}

template<typename STDContainer>
template<typename T>
inline const T & Container<STDContainer>::getSTL(const T & t)
{
  return t;
}

template<typename STDContainer>
inline const STDContainer & Container<STDContainer>::getSTL(const ThisClass & t)
{
  return t.m_items;
}

template<typename STDContainer>
inline const STDInitT & Container<STDContainer>::getSTL(const STDInitT & t)
{
  return t;
}

////////////////impementation////////////////

template<typename STDContainer>
Container<STDContainer>::Container() {}

template<typename STDContainer>
Container<STDContainer>::Container(const STDInitT & items) : m_items(items) {}

template<typename STDContainer>
template<typename T>
Container<STDContainer>::Container(const T &items) : m_items(getSTL(items)) {}

template<typename STDContainer>
void Container<STDContainer>::add(const STDInitT & items)
{
  insertHelper(items, m_items, m_items.size());
}

template<typename STDContainer>
template<typename T>
void Container<STDContainer>::add(const T & items)
{
  insertHelper(getSTL(items), m_items, m_items.size());
}

template<typename STDContainer>
template<typename T>
void Container<STDContainer>::insert(const T & items, int index)
{
  insertHelper(getSTL(items), m_items, index);
}

template<typename STDContainer>
template<typename T1, typename T2>
void Container<STDContainer>::replace(const T1 & oldItems, const T2 & newItems)
{
  replaceHelper(m_items, getSTL(oldItems), getSTL(newItems));
}

template<typename STDContainer>
template<typename T>
inline void Container<STDContainer>::replace(int index, int count, const T & newItem)
{
  removeHelper(m_items, index, count);
  insertHelper(index, getSTL(newItems));
}

template<typename STDContainer>
void Container<STDContainer>::removeByValue(const InnerType & item, int index /* = 0 */)
{
  removeByValueFirstHelper(m_items, item, index, size());
}

template<typename STDContainer>
void Container<STDContainer>::removeByValue(const InnerType & item, int index, int count)
{
  removeByValueFirstHelper(m_items, item, index, count);
}

template<typename STDContainer>
void Container<STDContainer>::removeByValueAll(const InnerType & item, int index /* = 0 */)
{
  removeByValueAllHelper(m_items, item, index, size());
}

template<typename STDContainer>
void Container<STDContainer>::removeByValueAll(const InnerType & item, int index, int count)
{
  removeByValueAllHelper(m_items, item, index, count);
}

template<typename STDContainer>
void Container<STDContainer>::remove(int index, int count /* = 1 */)
{
  removeHelper(m_items, index, count);
}

template<typename STDContainer>
int Container<STDContainer>::size()
{
  return m_items.size();
}

template<typename STDContainer>
void Container<STDContainer>::clear()
{
  m_items.clear();
}

template<typename STDContainer>
int Container<STDContainer>::find(InnerType item, int index /* = 0 */)
{
  if ( utils::isInRange(0, index, size() - 1) )
  {
    STDContainer::iterator it = std::find(std::next(m_items.begin(), index), m_items.end(), item);
    return it != m_items.end() ? std::distance(m_items.begin(), it) : -1;
  }
  return -1;
}

template<typename STDContainer>
Vector<int> Container<STDContainer>::findAll(const InnerType item)
{
  Vector<int> indexes;
  findAllHelper(indexes, m_items, item);
  return indexes;
}

template<typename STDContainer>
Container<STDContainer> Container<STDContainer>::sub(int index)
{
  ThisClass container;
  subHelper(m_items, container.m_items, index, m_items.size());
  return container;
}

template<typename STDContainer>
Container<STDContainer> Container<STDContainer>::sub(int index, int count)
{
  ThisClass container;
  subHelper(m_items, container.m_items, index, count);
  return container;
}

template<typename STDContainer>
void Container<STDContainer>::reverse(int index /* = 0 */)
{
  reverseHelper(m_items, index, m_items.size());
}

template<typename STDContainer>
void Container<STDContainer>::reverse(int index, int count)
{
  reverseHelper(m_items, index, count);
}

template<typename STDContainer>
void Container<STDContainer>::sort(bool ascending /* = true */)
{
  sortHelper(m_items, ascending);
}

template<typename STDContainer>
typename Container<STDContainer>::InnerType& Container<STDContainer>::operator[](int index)
{
  return *std::next(m_items.begin(), index);
}

template<typename STDContainer>
bool Container<STDContainer>::operator==(const ThisClass & container)
{
  return m_items == container.m_items;
}

template<typename STDContainer>
bool Container<STDContainer>::operator!=(const ThisClass & container)
{
  return !operator==(container);
}