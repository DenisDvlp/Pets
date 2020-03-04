//DContainerT.h
#pragma once
#include <initializer_list>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <random>
#include <ctime>
#include <iterator>
#include "DSfinae.h"

template<typename BaseContainer>
class DContainerT
{
private:

    static_assert(!is_const<BaseContainer>, "BaseContainer shall not be constant");
    static_assert(!is_ref<BaseContainer>, "BaseContainer shall not be a reference");
    static_assert(!is_ptr<BaseContainer>, "BaseContainer shall not be a pointer");
    static_assert(is_container<pure<BaseContainer>>, "BaseContainer shall be a container");
    static_assert(has_allocator_type<pure<BaseContainer>>, "BaseContainer shall be dynamic");
    static_assert(!has_key_type<pure<BaseContainer>>, "BaseContainer shall be sequential");
    static_assert(is_iterator_bidirectional<pure<BaseContainer>>, "BaseContainer shall be at least bidirectional");

public:
    using DContainerT_tag = void;

    using value_type = typename BaseContainer::value_type;
    using allocator_type = typename BaseContainer::allocator_type;
    using pointer = typename BaseContainer::pointer;
    using const_pointer = typename BaseContainer::const_pointer;
    using reference  = typename BaseContainer::reference;
    using const_reference = typename BaseContainer::const_reference;
    using size_type = typename BaseContainer::size_type;
    using difference_type = typename BaseContainer::difference_type;
    using iterator = typename BaseContainer::iterator;
    using const_iterator = typename BaseContainer::const_iterator;
    using reverse_iterator = typename BaseContainer::reverse_iterator;
    using const_reverse_iterator = typename BaseContainer::const_reverse_iterator;

    static constexpr size_type MAX_SIZE = std::numeric_limits<size_type>::max();

private: //sfinae block

    using AssertType = BaseContainer;
    template<typename T> static constexpr bool this_class_detected = is_same<T, DContainerT>;
    template<typename T> static constexpr bool this_baseclass_detected = is_same<T, BaseContainer>;
    template<typename T> static constexpr bool this_iterator_detected = is_same<iterator, T> || is_same<const_iterator, T>;
    template<typename T> static constexpr bool value_detected = is_convertible<value_type, unref<T>>;
    template<typename T> static constexpr bool container_detected = is_convertible<value_type, get_value_type<T>>;
    template<typename T> static constexpr bool array_detected = is_convertible<value_type, array_type<T>>;
    template<typename T> static constexpr bool size_type_detected = is_convertible<size_type, T>;
    template<typename T> static constexpr bool array_char_detected = array_detected<T> && is_same<array_type<T>, char>;
    template<typename T> static constexpr bool ptr_detected = is_ptr<unref<T>> && is_convertible<value_type, pure<T>>;
    template<typename T> static constexpr bool ptr_char_detected = ptr_detected<T> && is_same<T, char>;
    template<typename T> static constexpr bool iterator_detected = is_convertible<value_type, get_value_type<T>> || ptr_detected<T>;
    template<typename T1, typename T2> static constexpr bool iterator_range_detected = iterator_detected<T1> && iterator_detected<T2> && is_same<T1, T2>;
    template<typename T, typename S> static constexpr bool ptr_and_size_detected = (ptr_detected<T> || array_detected<T>) && size_type_detected<S>;
    template<typename T> static constexpr bool container_array_string_detected = container_detected<T> || array_detected<T> || ptr_char_detected<T>;
    template<typename T> static constexpr bool compare_pred2_detected = is_callable_match<T, bool, const value_type&, const value_type&>;
    template<typename T> static constexpr bool compare_pred1_detected = is_callable_match<T, bool, const value_type&>;
    template<typename T1, typename T2> static constexpr bool range_detected = iterator_range_detected<T1, T2> || ptr_and_size_detected<T1, T2>;


private:

    template<typename T>
    using std_init = std::initializer_list<T>;
    using std_list = std::list<value_type>;
    using std_vector = std::vector<value_type>;
    using std_deque = std::deque<value_type>;

public:

    DContainerT() = default;
    template<typename T> DContainerT(T&&);
    template<typename T> DContainerT(const std_init<T>&);
    template<typename T1, typename T2> DContainerT(T1, T2);

    template<typename T> DContainerT& operator=(T&&);
    template<typename T> DContainerT& operator=(const std_init<T>&);

    template<typename T> DContainerT& operator+=(T&&);
    template<typename T> DContainerT& operator+=(const std_init<T>&);

    template<typename T> DContainerT operator+(T&&);

    template<typename T> DContainerT& operator<<(T&&);

    template<typename T> bool operator==(T&&) const;
    template<typename T> bool operator!=(T&&) const;

    reference operator[](size_type index);
    const_reference operator[](size_type index) const;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
    const_iterator begin() const;
    const_iterator end() const;

    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    reference first();
    const_reference first() const;
    reference last();
    const_reference last() const;

    pointer data();
    const_pointer data() const;

    //size

    static constexpr size_type maxSize();
    constexpr size_type size() const;
    constexpr bool empty() const;
    void clear() noexcept;
    void resize(size_type);
    void reserve(size_type);
    void shrink();
    void release();

    //assign

    template<typename T> void assign(T&&);
    template<typename T> void assign(const std_init<T>&);
    template<typename T1, typename T2> void assign(T1, T2);

    void fill(const value_type&);
    void fill(size_type, const value_type&);

    //modifiers

    template<typename T> void push(T&&);
    template<typename T> void push(const std_init<T>&);
    template<typename T1, typename T2> void push(T1, T2);

    template<typename T> void front(T&&);
    template<typename T> void front(const std_init<T>&);
    template<typename T1, typename T2> void front(T1, T2);

    template<typename Iter, typename T> void insert(Iter, T&&);
    template<typename Iter, typename T> void insert(Iter, const std_init<T>&);
    template<typename Iter, typename T1, typename T2> void insert(Iter, T1, T2);

    template<typename... Args> void emplace_push(Args&&...);
    template<typename... Args> void emplace_front(Args&&...);
    template<typename Iter, typename... Args> void emplace_insert(Iter, Args&&...);

    value_type pop();
    template<typename Iter> value_type pop(Iter);
    value_type pop_front();

    template<typename Iter> void erase(Iter);
    template<typename Iter> void erase(Iter, Iter);

    template<typename T> void remove(const T&);
    template<typename T> void remove(const std_init<T>&);
    template<typename T1, typename T2> void remove(const T1&, const T2&);
    template<typename T, typename Pred2> void remove(const std_init<T>&, const Pred2&);
    template<typename T1, typename T2, typename Pred2> void remove(T1, T2, const Pred2&);

    template<typename T> auto find(const T&) const;
    template<typename T> auto find(const std_init<T>&) const;
    template<typename T1, typename T2> auto find(const T1&, const T2&) const;
    template<typename T, typename Pred2> auto find(const std_init<T>&, const Pred2&) const;
    template<typename T1, typename T2, typename Pred2> auto find(T1, T2, const Pred2&) const;

    template<typename T> auto find_all(const T&) const;
    template<typename T> auto find_all(const std_init<T>&) const;
    template<typename T1, typename T2> auto find_all(const T1&, const T2&) const;
    template<typename T, typename Pred2> auto find_all(const std_init<T>&, const Pred2&) const;
    template<typename T1, typename T2, typename Pred2> auto find_all(T1, T2, const Pred2&) const;

    template<typename T1, typename T2> void replace(const T1&, const T2&);
    template<typename T1, typename T2, typename T3> void replace(const T1&, const T2&, const T3&);
    template<typename T1, typename T2, typename T3, typename T4> void replace(const T1&, const T2&, const T3&, const T4&);
    template<typename T1, typename T2, typename T3, typename T4, typename Pred2> void replace(T1, T2, T3, T4, const Pred2&);

    template<typename T1, typename T2> void replace(const std_init<T1>&, const T2&);
    template<typename T1, typename T2, typename T3> void replace(const std_init<T1>&, const T2&, const T3&);
    template<typename T1, typename T2, typename T3, typename Pred2> void replace(const std_init<T1>&, T2, T3, const Pred2&);

    template<typename T1, typename T2> void replace(const T1&, const std_init<T2>&);
    template<typename T1, typename T2, typename T3> void replace(T1, T2, const std_init<T3>&);
    template<typename T1, typename T2, typename Pred2> void replace(const T1&, const std_init<T2>&, const Pred2&);
    template<typename T1, typename T2, typename T3, typename Pred2> void replace(T1, T2, const std_init<T3>&, const Pred2&);

    template<typename T1, typename T2> void replace(const std_init<T1>&, const std_init<T2>&);
    template<typename T1, typename T2, typename Pred2> void replace(const std_init<T1>&, const std_init<T2>&, const Pred2&);

    //operations

    void sort();
    template<typename Pred2> void sort(Pred2 pred);

    void shuffle();

    void reverse();

    template<typename T> auto split(const T&);
    template<typename T> auto split(const std_init<T>&);
    template<typename T1, typename T2> auto split(T1, T2);

private:

    template<typename T> auto iterWhere(T) const;
    template<typename T1, typename T2> auto iterBegin(T1, T2) const;
    template<typename T1, typename T2> auto iterEnd(T1, T2) const;

    template<typename T> auto itemsBegin(T&&) const;
    template<typename T> auto itemsEnd(T&&) const;

private:

    BaseContainer m_items;
};

template<typename T> using is_DContainerT = typename pure<T>::DContainerT_tag;

///////////////////////////implementation///////////////////////////////

//CONSTRUCTORS

template<typename BaseContainer>
template<typename T>
DContainerT<BaseContainer>::DContainerT(T&& items)
{
    assign(std::forward<T>(items));
}

template<typename BaseContainer>
template<typename T>
DContainerT<BaseContainer>::DContainerT(const std_init<T>& items)
{
    assign(items);
}

template<typename BaseContainer>
template<typename T1, typename T2>
DContainerT<BaseContainer>::DContainerT(T1 begin, T2 end)
{
    assign(begin, end);
}

//OPERATORS

template<typename BaseContainer>
template<typename T>
DContainerT<BaseContainer>& DContainerT<BaseContainer>::operator=(T&& items)
{
    assign(std::forward<T>(items));
    return *this;
}

template<typename BaseContainer>
template<typename T>
DContainerT<BaseContainer>& DContainerT<BaseContainer>::operator=(const std_init<T>& items)
{
    assign(items);
    return *this;
}

template<typename BaseContainer>
template<typename T>
DContainerT<BaseContainer>& DContainerT<BaseContainer>::operator+=(T&& items)
{
    push(std::forward<T>(items));
    return *this;
}

template<typename BaseContainer>
template<typename T>
DContainerT<BaseContainer>& DContainerT<BaseContainer>::operator+=(const std_init<T>& items)
{
    push(items);
    return *this;
}

template<typename BaseContainer>
template<typename T>
DContainerT<BaseContainer> DContainerT<BaseContainer>::operator+(T&& items)
{
    auto result = *this;
    result.push(std::forward<T>(items));
    return result;
}

template<typename T1, typename T2, typename = IF<!feature_detected<is_DContainerT, T1>>>
DContainerT<T2> operator+(T1&& items, const DContainerT<T2>& container)
{
    DContainerT<T2> result = std::forward<T1>(items);
    result.push(container);
    return result;
}

template<typename BaseContainer>
template<typename T>
DContainerT<BaseContainer>& DContainerT<BaseContainer>::operator<<(T&& items)
{
    push(std::forward<T>(items));
    return *this;
}

template<typename BaseContainer>
template<typename T>
inline bool DContainerT<BaseContainer>::operator==(T&& items) const
{
    return std::equal(cbegin(), cend(), itemsBegin(items), itemsEnd(items));
}

template<typename BaseContainer>
template<typename T>
inline bool DContainerT<BaseContainer>::operator!=(T&& items) const
{
    return !(operator==(items));
}

template<typename T1, typename T2, typename = IF<!feature_detected<is_DContainerT, T1>>>
inline bool operator==(const T1& items, const DContainerT<T2>& container)
{
    return container == items;
}

template<typename T1, typename T2, typename = IF<!feature_detected<is_DContainerT, T1>>>
inline bool operator!=(const T1& items, const DContainerT<T2>& container)
{
    return container != items;
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::operator[](size_type index) -> reference
{
    return const_cast<reference>(const_cast<const DContainerT*>(this)->operator[](index));
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::operator[](size_type index) const -> const_reference
{
    if constexpr (is_iterator_random<BaseContainer>)
    {
        return m_items[index];
    }
    else
    {
        return *std::next(begin(), index);
    }
}

//ITERATORS

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::begin() -> iterator
{
    return m_items.begin();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::end() -> iterator
{
    return m_items.end();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::cbegin() const -> const_iterator
{
    return m_items.cbegin();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::cend() const -> const_iterator
{
    return m_items.cend();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::begin() const -> const_iterator
{
    return m_items.begin();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::end() const -> const_iterator
{
    return m_items.end();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::rbegin() -> reverse_iterator
{
    return m_items.rbegin();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::rend() -> reverse_iterator
{
    return m_items.rend();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::crbegin() const -> const_reverse_iterator
{
    return m_items.crbegin();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::crend() const -> const_reverse_iterator
{
    return m_items.crend();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::rbegin() const -> const_reverse_iterator
{
    return m_items.rbegin();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::rend() const -> const_reverse_iterator
{
    return m_items.rend();
}

//FIRST

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::first() -> reference
{
    return m_items.front();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::first() const -> const_reference
{
    return m_items.front();
}

//LAST

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::last() -> reference
{
    return m_items.back();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::last() const -> const_reference
{
    return m_items.back();
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::data() -> pointer
{
    if constexpr(has_method_data<BaseContainer>)
    {
        return m_items.data();
    }
    else
    {
        return nullptr;
    }
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::data() const -> const_pointer
{
    if constexpr(has_method_data<BaseContainer>)
    {
        return m_items.data();
    }
    else
    {
        return nullptr;
    }
}

//SIZE

template<typename BaseContainer>
inline constexpr auto DContainerT<BaseContainer>::maxSize() -> size_type
{
    return MAX_SIZE;
}

template<typename BaseContainer>
inline constexpr auto DContainerT<BaseContainer>::size() const -> size_type
{
    return m_items.size();
}

template<typename BaseContainer>
inline constexpr bool DContainerT<BaseContainer>::empty() const
{
    return m_items.empty();
}

template<typename BaseContainer>
inline void DContainerT<BaseContainer>::clear() noexcept
{
    return m_items.clear();
}

template<typename BaseContainer>
inline void DContainerT<BaseContainer>::resize(size_type size)
{
    m_items.resize(size);
}

template<typename BaseContainer>
inline void DContainerT<BaseContainer>::reserve(size_type size)
{
    if constexpr (has_method_reserve<BaseContainer>)
    {
        m_items.reserve(size);
    }
}

template<typename BaseContainer>
inline void DContainerT<BaseContainer>::shrink()
{
    if constexpr (is_iterator_random<BaseContainer>)
    {
        m_items.shrink_to_fit();
    }
}

template<typename BaseContainer>
inline void DContainerT<BaseContainer>::release()
{
    m_items.resize(0);
    m_items.shrink_to_fit();
}

//ASSIGN

template<typename BaseContainer>
template<typename T>
void DContainerT<BaseContainer>::assign(T&& items)
{
    if constexpr (this_class_detected<T>)
    {
        m_items = std::forward<T>(items).m_items;
    }
    else if constexpr (this_baseclass_detected<T>)
    {
        m_items = std::forward<T>(items);
    }
    else
    {
        assign(itemsBegin(items), itemsEnd(items));
    }
}

template<typename BaseContainer>
template<typename T>
void DContainerT<BaseContainer>::assign(const std_init<T>& items)
{
    assign(items.begin(), items.end());
}

template<typename BaseContainer>
template<typename T1, typename T2>
inline void DContainerT<BaseContainer>::assign(T1 begin, T2 end)
{
    m_items.assign(iterBegin(begin, end), iterEnd(begin, end));
}

template<typename BaseContainer>
inline void DContainerT<BaseContainer>::fill(const value_type& value)
{
    for (auto& item : m_items)
    {
        item = value;
    }
}

template<typename BaseContainer>
inline void DContainerT<BaseContainer>::fill(size_type size, const value_type& value)
{
    for (auto& item : m_items)
    {
        item = value;
        if (!(size--))
        {
            break;
        }
    }
}

//PUSH, FRONT

template<typename BaseContainer>
template<typename T>
void DContainerT<BaseContainer>::push(T&& items)
{
    insert(cend(), std::forward<T>(items));
}

template<typename BaseContainer>
template<typename T>
void DContainerT<BaseContainer>::push(const std_init<T>& items)
{
    insert(cend(), items.begin(), items.end());
}

template<typename BaseContainer>
template<typename T1, typename T2>
inline void DContainerT<BaseContainer>::push(T1 begin, T2 end)
{
    insert(cend(), begin, end);
}

template<typename BaseContainer>
template<typename T>
inline void DContainerT<BaseContainer>::front(T&& items)
{
    insert(cbegin(), std::forward<T>(items));
}

template<typename BaseContainer>
template<typename T>
inline void DContainerT<BaseContainer>::front(const std_init<T>& items)
{
    insert(cbegin(), items.begin(), items.end());
}

template<typename BaseContainer>
template<typename T1, typename T2>
inline void DContainerT<BaseContainer>::front(T1 begin, T2 end)
{
    insert(cbegin(), begin, end);
}

//INSERT

template<typename BaseContainer>
template<typename Iter, typename T>
inline void DContainerT<BaseContainer>::insert(Iter where, T&& items)
{
    if constexpr (value_detected<T>)
    {
        m_items.insert(iterWhere(where), std::forward<T>(items));
    }
    else
    {
        insert(where, itemsBegin(items), itemsEnd(items));
    }
}

template<typename BaseContainer>
template<typename Iter, typename T>
inline void DContainerT<BaseContainer>::insert(Iter where, const std_init<T>& items)
{
    insert(where, items.begin(), items.end());
}

template<typename BaseContainer>
template<typename Iter, typename T1, typename T2>
inline void DContainerT<BaseContainer>::insert(Iter where, T1 begin, T2 end)
{
    m_items.insert(iterWhere(where), iterBegin(begin, end), iterEnd(begin, end));
}

template<typename BaseContainer>
template<typename... Args>
inline void DContainerT<BaseContainer>::emplace_push(Args&&... args)
{
    emplace_insert(cend(), std::forward<Args>(args)...);
}

template<typename BaseContainer>
template<typename... Args>
inline void DContainerT<BaseContainer>::emplace_front(Args&&... args)
{
    emplace_insert(cbegin(), std::forward<Args>(args)...);
}

template<typename BaseContainer>
template<typename Iter, typename... Args>
inline void DContainerT<BaseContainer>::emplace_insert(Iter where, Args&&... args)
{
    if constexpr (has_method_emplace<BaseContainer, Args...>)
    {
        m_items.emplace(iterWhere(where), std::forward<Args>(args)...);
    }
    else
    {
        insert(where, std::forward<Args>(args)...);
    }
}

//POP

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::pop() -> value_type
{
    return pop(crbegin());
}

template<typename BaseContainer>
inline auto DContainerT<BaseContainer>::pop_front() -> value_type
{
    return pop(cbegin());
}

template<typename BaseContainer>
template<typename Iter>
auto DContainerT<BaseContainer>::pop(Iter where) -> value_type
{
    auto result = std::move(*iterWhere(where));
    erase(where);
    return result;
}

//ERASE

template<typename BaseContainer>
template<typename Iter>
inline void DContainerT<BaseContainer>::erase(Iter where)
{
    m_items.erase(iterWhere(where));
}

template<typename BaseContainer>
template<typename Iter>
void DContainerT<BaseContainer>::erase(Iter begin, Iter end)
{
    if constexpr (has_method_base<Iter>)
    {
        m_items.erase(end.base(), begin.base());
    }
    else
    {
        m_items.erase(iterWhere(begin), iterWhere(end));
    }
}

template<typename BaseContainer>
template<typename T>
inline void DContainerT<BaseContainer>::remove(const T& items)
{
    if constexpr (compare_pred1_detected<T>)
    {
        if constexpr (has_method_remove<BaseContainer>)
        {
            m_items.remove_if(items);
        }
        else
        {
            m_items.erase(std::remove_if(begin(), end(), items), end());
        }
    }
    else if constexpr (value_detected<T>)
    {
        if constexpr (has_method_remove<BaseContainer>)
        {
            m_items.remove(items);
        }
        else
        {
            m_items.erase(std::remove(begin(), end(), items), end());
        }
    }
    else
    {
        remove(itemsBegin(items), itemsEnd(items), std::equal_to<>());
    }
}

template<typename BaseContainer>
template<typename T>
inline void DContainerT<BaseContainer>::remove(const std_init<T>& items)
{
    remove(items.begin(), items.end(), std::equal_to<>());
}

template<typename BaseContainer>
template<typename T1, typename T2>
inline void DContainerT<BaseContainer>::remove(const T1& begin, const T2& end)
{
    if constexpr (compare_pred2_detected<T2>)
    {
        remove(itemsBegin(begin), itemsEnd(begin), end);
    }
    else
    {
        remove(begin, end, std::equal_to<>());
    }
}

template<typename BaseContainer>
template<typename T, typename Pred2>
inline void DContainerT<BaseContainer>::remove(const std_init<T>& items, const Pred2& pred)
{
    static_assert(compare_pred2_detected<pred>, "parameter invalid");

    remove(items.begin(), items.end(), pred);
}

template<typename BaseContainer>
template<typename T1, typename T2, typename Pred2>
inline void DContainerT<BaseContainer>::remove(T1 b, T2 e, const Pred2& pred2)
{
    static_assert(compare_pred2_detected<Pred2>, "parameter invalid");

    const auto itBegin = iterBegin(b, e);
    const auto itEnd = iterEnd(b, e);
    const auto sizeDst = std::distance(itBegin, itEnd);

    if constexpr (is_iterator_random<BaseContainer>)
    {
        auto it = std::search(begin(), end(), itBegin, itEnd, pred2);
        DContainerT tmp(begin(), it);
        while (it != end())
        {
            auto itNext = std::next(it, sizeDst);
            it = std::search(itNext, end(), itBegin, itEnd, pred2);
            tmp.push(itNext, it);
        }
        *this = std::move(tmp);
    }
    else if constexpr (is_iterator_bidirectional<BaseContainer>)
    {
        auto it = std::search(begin(), end(), itBegin, itEnd, pred2);
        while (it != end())
        {
            auto itNext = std::next(it, sizeDst);
            m_items.erase(it, itNext);
            it = std::search(itNext, end(), itBegin, itEnd, pred2);
        }
    }
}

template<typename BaseContainer>
template<typename T>
inline auto DContainerT<BaseContainer>::find(const T& items) const
{
    if constexpr (compare_pred1_detected<T>)
    {
        return std::find_if(begin(), end(), items);
    }
    else if constexpr (value_detected<T>)
    {
        return std::find(begin(), end(), items);
    }
    else
    {
        return find(itemsBegin(items), itemsEnd(items), std::equal_to<>());
    }
}

template<typename BaseContainer>
template<typename T>
inline auto DContainerT<BaseContainer>::find(const std_init<T>& items) const
{
    return find(items.begin(), items.end(), std::equal_to<>());
}

template<typename BaseContainer>
template<typename T1, typename T2>
inline auto DContainerT<BaseContainer>::find(const T1& begin, const T2& end) const
{
    if constexpr (compare_pred2_detected<T2>)
    {
        return find(itemsBegin(begin), itemsEnd(begin), end);
    }
    else
    {
        return find(begin, end, std::equal_to<>());
    }
}

template<typename BaseContainer>
template<typename T, typename Pred2>
inline auto DContainerT<BaseContainer>::find(const std_init<T>& items, const Pred2& pred2) const
{
    return find(items.begin(), items.end(), pred2);
}

template<typename BaseContainer>
template<typename T1, typename T2, typename Pred2>
inline auto DContainerT<BaseContainer>::find(T1 begin, T2 end, const Pred2& pred2) const
{
    static_assert(compare_pred2_detected<Pred2>, "predicate invalid");

    return std::search(cbegin(), cend(), iterBegin(begin, end), iterEnd(begin, end), pred2);
}

template<typename BaseContainer>
template<typename T>
auto DContainerT<BaseContainer>::find_all(const T& items) const
{
    using Vector_iter = DContainerT<std::vector<decltype(begin())>>;

    if constexpr (compare_pred1_detected<T>)
    {
        Vector_iter iters;

        auto it = std::find_if(begin(), end(), items);
        while (it != end())
        {
            iters.push(it);
            it = std::find_if(++it, end(), items);
        }

        return iters;
    }
    else if constexpr (value_detected<T>)
    {
        Vector_iter iters;

        auto it = std::find(begin(), end(), items);
        while (it != end())
        {
            iters.push(it);
            it = std::find(++it, end(), items);
        }

        return iters;
    }
    else
    {
        static_assert(container_array_string_detected<T>, "parameter invalid");

        return find_all(itemsBegin(items), itemsEnd(items));
    }
}

template<typename BaseContainer>
template<typename T>
inline auto DContainerT<BaseContainer>::find_all(const std_init<T>& items) const
{
    return find_all(items.begin(), items.end());
}

template<typename BaseContainer>
template<typename T1, typename T2>
inline auto DContainerT<BaseContainer>::find_all(const T1& begin, const T2& end) const
{
    if constexpr (compare_pred2_detected<T2>)
    {
        return find_all(itemsBegin(begin), itemsEnd(begin), end);
    }
    else
    {
        return find_all(begin, end, std::equal_to<>());
    }
}

template<typename BaseContainer>
template<typename T, typename Pred2>
inline auto DContainerT<BaseContainer>::find_all(const std_init<T>& items, const Pred2& pred) const
{
    return find_all(items.begin(), items.end(), pred);
}

template<typename BaseContainer>
template<typename T1, typename T2, typename Pred2>
auto DContainerT<BaseContainer>::find_all(T1 b, T2 e, const Pred2& pred2) const
{
    static_assert(compare_pred2_detected<Pred2>, "predicate invalid");

    using Vector_iter = DContainerT<std::vector<decltype(begin())>>;

    Vector_iter iters;

    const auto itBegin = iterBegin(b, e);
    const auto itEnd = iterEnd(b, e);
    const auto size = std::distance(itBegin, itEnd);

    auto it = std::search(begin(), end(), itBegin, itEnd, pred2);
    while (it != end())
    {
        iters.push(it);
        std::advance(it, size);
        it = std::search(it, end(), itBegin, itEnd, pred2);
    }

    return iters;
}

template<typename BaseContainer>
template<typename T1, typename T2>
inline void DContainerT<BaseContainer>::replace(const T1& dst, const T2& src)
{
    replace(itemsBegin(dst), itemsEnd(dst), itemsBegin(src), itemsEnd(src), std::equal_to<>());
}

template<typename BaseContainer>
template<typename T1, typename T2, typename T3>
inline void DContainerT<BaseContainer>::replace(const T1& dst, const T2& src, const T3& pred)
{
    if constexpr (compare_pred2_detected<T3>)
    {
        replace(itemsBegin(dst), itemsEnd(dst), itemsBegin(src), itemsEnd(src), pred);
    }
    else if constexpr (range_detected<T1, T2>)
    {
        replace(dst, src, itemsBegin(src), itemsEnd(src), std::equal_to<>());
    }
    else
    {
        replace(itemsBegin(dst), itemsEnd(dst), src, pred, std::equal_to<>());
    }
}

template<typename BaseContainer>
template<typename T1, typename T2, typename T3, typename T4>
inline void DContainerT<BaseContainer>::replace(const T1& dst, const T2& dst2, const T3& src, const T4& src2)
{
    if constexpr (compare_pred2_detected<T4>)
    {
        if constexpr (range_detected<T1, T2>)
        {
            replace(dst, dst2, itemsBegin(src), itemsEnd(src), src2);
        }
        else
        {
            replace(itemsBegin(src), itemsEnd(src), dst2, src, src2);
        }
    }
    else
    {
        replace(dst, dst2, src, src2, std::equal_to<>());
    }
}

template<typename BaseContainer>
template<typename T1, typename T2, typename T3, typename T4, typename Pred2>
void DContainerT<BaseContainer>::replace(T1 dst, T2 dst2, T3 src, T4 src2, const Pred2& pred)
{
    static_assert(compare_pred2_detected<Pred2>, "parameter invalid");

    const auto itDstBegin = iterBegin(dst, dst2);
    const auto itDstEnd = iterEnd(dst, dst2);
    const auto sizeDst = std::distance(itDstBegin, itDstEnd);

    if constexpr (is_iterator_random<BaseContainer>)
    {
        auto it = std::search(begin(), end(), itDstBegin, itDstEnd, pred);
        DContainerT tmp(begin(), it);
        while (it != end())
        {
            tmp.push(src, src2);
            auto itNext = std::next(it, sizeDst);
            it = std::search(itNext, end(), itDstBegin, itDstEnd, pred);
            tmp.push(itNext, it);
        }
        *this = std::move(tmp);
    }
    else if constexpr (is_iterator_bidirectional<BaseContainer>)
    {
        auto it = std::search(begin(), end(), itDstBegin, itDstEnd, pred);
        while (it != end())
        {
            auto itNext = std::next(it, sizeDst);
            m_items.erase(it, itNext);
            insert(itNext, src, src2);
            it = std::search(itNext, end(), itDstBegin, itDstEnd, pred);
        }
    }
}

template<typename BaseContainer>
template<typename T1, typename T2>
inline void DContainerT<BaseContainer>::replace(const std_init<T1>& dst, const T2& src)
{
    replace(dst.begin(), dst.end(), itemsBegin(src), itemsEnd(src), std::equal_to<>());
}

template<typename BaseContainer>
template<typename T1, typename T2, typename T3>
inline void DContainerT<BaseContainer>::replace(const std_init<T1>& dst, const T2& src, const T3& src2)
{
    if constexpr (compare_pred2_detected<T3>)
    {
        replace(dst.begin(), dst.end(), itemsBegin(src), itemsEnd(src), src2);
    }
    else
    {
        replace(dst.begin(), dst.end(), src, src2, std::equal_to<>());
    }
}

template<typename BaseContainer>
template<typename T1, typename T2, typename T3, typename Pred2>
inline void DContainerT<BaseContainer>::replace(const std_init<T1>& dst, T2 src, T3 src2, const Pred2& pred)
{
    replace(dst.begin(), dst.end(), src, src2, pred);
}

template<typename BaseContainer>
template<typename T1, typename T2>
inline void DContainerT<BaseContainer>::replace(const T1& dst, const std_init<T2>& src)
{
    replace(itemsBegin(dst), itemsEnd(dst), src.begin(), src.end(), std::equal_to<>());
}

template<typename BaseContainer>
template<typename T1, typename T2, typename T3>
inline void DContainerT<BaseContainer>::replace(T1 dst, T2 dst2, const std_init<T3>& src)
{
    replace(dst, dst2, src.begin(), src.end(), std::equal_to<>());
}

template<typename BaseContainer>
template<typename T1, typename T2, typename Pred2>
inline void DContainerT<BaseContainer>::replace(const T1& dst, const std_init<T2>& src, const Pred2& pred)
{
    replace(itemsBegin(dst), itemsEnd(dst), src.begin(), src.end(), pred);
}

template<typename BaseContainer>
template<typename T1, typename T2, typename T3, typename Pred2>
inline void DContainerT<BaseContainer>::replace(T1 dst, T2 dst2, const std_init<T3>& src, const Pred2& pred)
{
    replace(dst, dst2, src.begin(), src.end(), pred);
}

template<typename BaseContainer>
template<typename T1, typename T2>
inline void DContainerT<BaseContainer>::replace(const std_init<T1>& dst, const std_init<T2>& src)
{
    replace(dst.begin(), dst.end(), src.begin(), src.end(), std::equal_to<>());
}

template<typename BaseContainer>
template<typename T1, typename T2, typename Pred2>
inline void DContainerT<BaseContainer>::replace(const std_init<T1>& dst, const std_init<T2>& src, const Pred2& pred)
{
    replace(dst.begin(), dst.end(), src.begin(), src.end(), pred);
}

//OPERATIONS

template<typename BaseContainer>
inline void DContainerT<BaseContainer>::sort()
{
    if constexpr (has_method_sort<BaseContainer>)
    {
        m_items.sort();
    }
    else
    {
        std::sort(m_items.begin(), m_items.end());
    }
}

template<typename BaseContainer>
template<typename Pred2>
inline void DContainerT<BaseContainer>::sort(Pred2 pred2)
{
    if constexpr (has_method_sort<BaseContainer, Pred2>)
    {
        m_items.sort(pred2);
    }
    else
    {
        std::sort(m_items.begin(), m_items.end(), pred2);
    }
}

template<typename BaseContainer>
inline void DContainerT<BaseContainer>::reverse()
{
    if constexpr (has_method_reverse<BaseContainer>)
    {
        m_items.reverse();
    }
    else
    {
        std::reverse(begin(), end());
    }
}

template<typename BaseContainer>
inline void DContainerT<BaseContainer>::shuffle()
{
    if constexpr (is_iterator_random<BaseContainer>)
    {
        std::shuffle(begin(), end(), std::mt19937(time(0)));
    }
    else if constexpr (is_iterator_bidirectional<BaseContainer>)
    {
        std::vector<std::reference_wrapper<value_type>> temp(begin(), end());
        std::shuffle(temp.begin(), temp.end(), std::mt19937(time(0)));
        assign(temp.cbegin(), temp.cend());
    }
}

template<typename BaseContainer>
template<typename T>
inline auto DContainerT<BaseContainer>::split(const T& items)
{
    return split(itemsBegin(items), itemsEnd(items));
}

template<typename BaseContainer>
template<typename T>
inline auto DContainerT<BaseContainer>::split(const std_init<T>& items)
{
    return split(items.begin(), items.end());
}

template<typename BaseContainer>
template<typename T1, typename T2>
inline auto DContainerT<BaseContainer>::split(T1 b, T2 e)
{
    DContainerT<std::vector<DContainerT>> result;

    const auto itBegin = iterBegin(b, e);
    const auto itEnd = iterEnd(b, e);
    const auto size = std::distance(itBegin, itEnd);

    const auto findResults = find_all(itBegin, itEnd);
    auto it = cbegin();

    for (const auto itFind : findResults)
    {
        if (it != itFind)
        {
            result.emplace_push(it, itFind);
        }
        it = std::next(itFind, size);
    }

    if (it != cend())
    {
        result.emplace_push(it, cend());
    }

    return result;
}

//ITERATOR ADAPTERS

template<typename BaseContainer>
template<typename T>
inline auto DContainerT<BaseContainer>::iterWhere(T i) const
{
    if constexpr (size_type_detected<T>)
    {
        return std::next(cbegin(), i);
    }
    else if constexpr (has_method_base<T>)
    {
        return --(i.base());
    }
    else
    {
        static_assert(iterator_detected<T>, "indexer invalid");

        return i;
    }
}

template<typename BaseContainer>
template<typename T1, typename T2>
inline auto DContainerT<BaseContainer>::iterBegin(T1 begin, T2 end) const
{
    static_assert(range_detected<T1, T2>, "indexer invalid");

    return begin;
}

template<typename BaseContainer>
template<typename T1, typename T2>
inline auto DContainerT<BaseContainer>::iterEnd(T1 begin, T2 end) const
{
    if constexpr (ptr_and_size_detected<T1, T2>)
    {
        return begin + end;
    }
    else
    {
        static_assert(iterator_range_detected<T1, T2>, "indexer invalid");

        return end;
    }
}

template<typename BaseContainer>
template<typename T>
inline auto DContainerT<BaseContainer>::itemsBegin(T&& items) const
{
    if constexpr (value_detected<T>)
    {
        return &items;
    }
    else if constexpr (container_detected<T>)
    {
        return items.begin();
    }
    else
    {
        static_assert(array_detected<T> || ptr_char_detected<T>, "parameter invalid");

        return items;
    }
}

template<typename BaseContainer>
template<typename T>
inline auto DContainerT<BaseContainer>::itemsEnd(T&& items) const
{
    if constexpr (value_detected<T>)
    {
        return &items + 1;
    }
    else if constexpr (container_detected<T>)
    {
        return items.end();
    }
    else if constexpr (array_detected<T>)
    {
        if constexpr (array_char_detected<T>)
        {
            return items + array_size<T> - (items[array_size<T> - 1] == 0 ? 1 : 0);
        }
        else
        {
            return items + array_size<T>;
        }
    }
    else if constexpr (ptr_char_detected<T>)
    {
        return items + strlen(items);
    }
    else
    {
        static_assert(static_assert_false<AssertType>, "parameter invalid");
    }
}
