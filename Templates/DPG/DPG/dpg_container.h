//Container.h
#pragma once
#include <initializer_list>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <random>
#include <ctime>
#include <iterator>
#include "dpg_sfinae.h"

#pragma warning(push)
#pragma warning(disable : 4544)
#pragma warning(disable : 4348)

namespace dpg
{

template<typename STDContainer>
class ContainerT
{
    using ThisContainer = sfinae::pure<STDContainer>;

public:

    using value_type = typename ThisContainer::value_type;
    using iterator = typename ThisContainer::iterator;
    using reverse_iterator = typename ThisContainer::reverse_iterator;
    using const_reverse_iterator = typename ThisContainer::const_reverse_iterator;
    using const_iterator = typename ThisContainer::const_iterator;
    using allocator_type = typename ThisContainer::allocator_type;

    static const size_t MAX_SIZE = std::numeric_limits<size_t>::max();
    static const size_t NOT_FOUND = MAX_SIZE;

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
    template <typename T>
    static constexpr bool is_value_type_v = sfinae::is_same_v<value_type, T> || sfinae::can_construct_v<value_type, T>;
    template<typename T>
    using is_value_type = sfinae::boolean<is_value_type_v<T>>;
    template<typename T>
    using is_container = sfinae::boolean<sfinae::is_container_v<T> && !is_value_type<T>::value>;
    template<typename T>
    using if_container_value = sfinae::if_t<sfinae::is_container_v<T> || is_value_type<T>::value>;
    template<typename T>
    using if_container_predicate1_value = sfinae::if_t<sfinae::is_container_v<T> || sfinae::is_unary_predicate_v<T, value_type> || is_value_type<T>::value>;
    template<typename T>
    using if_predicate2 = sfinae::if_t<sfinae::is_binary_predicate_v<T, value_type>>;
    template<typename T>
    using is_predicate1 = sfinae::is_unary_predicate<T, value_type>;
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

    class StringWrapper
    {
    public:
        using value_type = const char;
        using iterator = char*;
        using const_iterator = const char*;
    public:
        StringWrapper(const char* text)
            : text(text)
            , len(strlen(text))
        {}
        const_iterator cbegin() const
        {
            return text;
        }
        const_iterator cend() const
        {
            return text + len;
        }
        size_t size() const
        {
            return len;
        }
        bool empty() const
        {
            return len == 0;
        }
        operator const char* () const
        {
            return text;
        }
    private:
        const char* text = nullptr;
        const size_t len = 0;
    };

public:

    template<typename T, typename = if_another_container<T>>
    Container(T&&);
    Container() = default;
    Container(const ThisInit&);
    Container(const ThisContainer&);
    Container(ThisContainer&&) noexcept;
    Container(const ThisClass&);
    Container(ThisClass&&) noexcept;
    Container(const char*);

    template<typename T, typename = if_container_value<T>>
    Container& operator=(T&&);
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

    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    value_type first() const;
    value_type last() const;

    constexpr size_t size() const;
    constexpr bool empty() const;

    template<typename T, typename = if_container_value<T>>
    void add(T&&);
    void add(const ThisInit&);

    template<typename T>
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
    void resize(size_t);
    void reserve(size_t);
    void clear();

    Container sub(size_t, size_t) const;

    vector_value toStdVector() const;
    vector_value toStdVector(size_t, size_t) const;
    list_value toStdList() const;
    list_value toStdList(size_t, size_t) const;
    deque_value toStdDeque() const;
    deque_value toStdDeque(size_t, size_t) const;
    std::string toStdString() const;
    std::string toStdString(size_t, size_t) const;

    STDContainer& asStd();
    const STDContainer& asStd() const;

    void rotateLeft(size_t);
    void rotateRight(size_t);

    template<typename T, typename = if_container_value<T>>
    void merge(T&&);
    void merge(const ThisInit&);
    void merge(const char*);
    template<typename T1, typename T2, typename = if_container_value<T1>, typename = if_predicate2<T2>>
    void merge(T1&&, T2&&);
    template<typename T, typename = if_predicate2<T>>
    void merge(const ThisInit&, T&&);
    template<typename T, typename = if_predicate2<T>>
    void merge(const char*, T&&);

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
    static bool equal_helper4(const ThisContainer&, const value_type&, boolean_true);
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
    static const_iterator find_helper3(const_iterator, const_iterator, const value_type&, boolean_true);
    template<typename T> //value_type
    static const_iterator find_helper3(const_iterator, const_iterator, T&&, boolean_false);
    template<typename T> //predicate1
    static const_iterator find_helper4(const_iterator, const_iterator, T&&, boolean_true);
    template<typename T> //container
    static const_iterator find_helper4(const_iterator, const_iterator, T&&, boolean_false);

    template<typename T1, typename T2>
    static void remove_helper(T1&, T2&&);
    template<typename T> //value_type
    static void remove_helper2(T&, const value_type&, boolean_true);
    static void remove_helper2(list_value&, const value_type&, boolean_true);
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
    static void reserve_helper(T&&, size_t);
    static void reserve_helper(vector_value&, size_t);
    static void reserve_helper(std::string&, size_t);

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

template<typename STDContainer>
template<typename T, typename = if_another_container<T>>
Container<STDContainer>::Container(T&& items)
    : m_items(items.begin(), items.end())
{}

template<typename STDContainer>
Container<STDContainer>::Container(const ThisInit& items)
    : m_items(items)
{}

template<typename STDContainer>
Container<STDContainer>::Container(const ThisContainer& items)
    : m_items(items)
{}

template<typename STDContainer>
Container<STDContainer>::Container(ThisContainer&& items) noexcept
    : m_items(std::move(items))
{}

template<typename STDContainer>
Container<STDContainer>::Container(const ThisClass& items)
    : m_items(items.m_items)
{}

template<typename STDContainer>
Container<STDContainer>::Container(ThisClass&& items) noexcept
    : m_items(std::move(items.m_items))
{}

template<>
Container<std::string>::Container(const char* text)
    : m_items(text)
{}

//OPERATOR =

template<typename STDContainer>
template<typename T, typename = if_container_value<T>>
Container<STDContainer>& Container<STDContainer>::operator=(T&& items)
{
    assign_helper(m_items, std::forward<T>(items));
    return *this;
}

template<typename STDContainer>
Container<STDContainer>& Container<STDContainer>::operator=(const ThisInit& items)
{
    assign_helper(m_items, items);
    return *this;
}

//OPERATOR +=

template<typename STDContainer>
template<typename T, typename = if_container_value<T>>
Container<STDContainer>& Container<STDContainer>::operator+=(T&& items)
{
    add(std::forward<T>(items));
    return *this;
}

template<typename STDContainer>
Container<STDContainer>& Container<STDContainer>::operator+=(const ThisInit& items)
{
    add(items);
    return *this;
}

//OPERATOR +

template<typename STDContainer>
template<typename T, typename = if_container_value<T>>
Container<STDContainer> Container<STDContainer>::operator+(T&& items) const
{
    Container<STDContainer> result(m_items);
    result.add(std::forward<T>(items));
    return result;
}

//OPERATOR ==

template<typename STDContainer>
template<typename T, typename = if_container_value<T>>
bool Container<STDContainer>::operator==(T&& items) const
{
    return equal_helper(m_items, items);
}

//OPERATOR !=

template<typename STDContainer>
template<typename T, typename = if_container_value<T>>
bool Container<STDContainer>::operator!=(T&& items) const
{
    return !operator==(items);
}

//OPERATOR []

template<typename STDContainer>
auto Container<STDContainer>::operator[](size_t index) -> value_type&
{
    return *std::next(begin(), index);
}

template<typename STDContainer>
auto Container<STDContainer>::operator[](size_t index) const -> const value_type&
{
    return *std::next(begin(), index);
}

//OPERATOR CONTAINER

template<typename STDContainer>
Container<STDContainer>::operator ThisContainer() const
{
    return m_items;
}

//ITERATORS

template<typename STDContainer>
inline auto Container<STDContainer>::begin() -> iterator
{
    return m_items.begin();
}

template<typename STDContainer>
inline auto Container<STDContainer>::end() -> iterator
{
    return m_items.end();
}

template<typename STDContainer>
inline auto Container<STDContainer>::cbegin() const -> const_iterator
{
    return m_items.cbegin();
}

template<typename STDContainer>
inline auto Container<STDContainer>::cend() const -> const_iterator
{
    return m_items.cend();
}

template<typename STDContainer>
inline auto Container<STDContainer>::begin() const -> const_iterator
{
    return m_items.begin();
}

template<typename STDContainer>
inline auto Container<STDContainer>::end() const -> const_iterator
{
    return m_items.end();
}

template<typename STDContainer>
inline auto Container<STDContainer>::rbegin() -> reverse_iterator
{
    return m_items.rbegin();
}

template<typename STDContainer>
inline auto Container<STDContainer>::rend() -> reverse_iterator
{
    return m_items.rend();
}

template<typename STDContainer>
inline auto Container<STDContainer>::crbegin() const -> const_reverse_iterator
{
    return m_items.crbegin();
}

template<typename STDContainer>
inline auto Container<STDContainer>::crend() const -> const_reverse_iterator
{
    return m_items.crend();
}

template<typename STDContainer>
inline auto Container<STDContainer>::rbegin() const -> const_reverse_iterator
{
    return m_items.rbegin();
}

template<typename STDContainer>
inline auto Container<STDContainer>::rend() const -> const_reverse_iterator
{
    return m_items.rend();
}

//FIRST

template<typename STDContainer>
inline auto Container<STDContainer>::first() const -> value_type
{
    return m_items.front();
}

//LAST

template<typename STDContainer>
inline auto Container<STDContainer>::last() const -> value_type
{
    return m_items.back();
}

//SIZE

template<typename STDContainer>
inline constexpr size_t Container<STDContainer>::size() const
{
    return m_items.size();
}

//EMPTY

template<typename STDContainer>
inline constexpr bool Container<STDContainer>::empty() const
{
    return m_items.empty();
}

//ADD

template<typename STDContainer>
template<typename T, typename = if_container_value<T>>
void Container<STDContainer>::add(T&& items)
{
   insert_helper(m_items, end(), std::forward<T>(items));
}

template<typename STDContainer>
void Container<STDContainer>::add(const ThisInit& items)
{
    insert_helper(m_items, end(), items);
}

//INSERT

template<typename STDContainer>
template<typename T>
void Container<STDContainer>::insert(size_t index, T&& items)
{
    if (index < size())
    {
        insert_helper(m_items, std::next(begin(), index), std::forward<T>(items));
    }
}

template<typename STDContainer>
void Container<STDContainer>::insert(size_t index, const ThisInit& items)
{
    if (index < size())
    {
        insert_helper(m_items, std::next(begin(), index), items);
    }
}

//REMOVE

template<typename STDContainer>
template<typename T, typename = if_container_predicate1_value<T>>
void Container<STDContainer>::remove(T&& items)
{
    remove_helper(m_items, items);
}

template<typename STDContainer>
void Container<STDContainer>::remove(const ThisInit& items)
{
    remove_helper(m_items, items);
}

//ERASE

template<typename STDContainer>
void Container<STDContainer>::erase(size_t index, size_t size)
{
    erase_helper(m_items, index, size);
}

//FIND

template<typename STDContainer>
template<typename T, typename = if_container_predicate1_value<T>>
size_t Container<STDContainer>::find(T&& items) const
{
    size_t result;
    find_helper(result, m_items, items);
    return result;
}

template<typename STDContainer>
size_t Container<STDContainer>::find(const ThisInit& items) const
{
    size_t result;
    find_helper(result, m_items, items);
    return result;
}

template<typename STDContainer>
template<typename T, typename = if_container_predicate1_value<T>>
Container<std::vector<size_t>> Container<STDContainer>::findAll(T&& items) const
{
    Vector_size results;
    find_helper(results, m_items, std::forward<T>(items));
    return results;
}

template<typename STDContainer>
Container<std::vector<size_t>> Container<STDContainer>::findAll(const ThisInit& items) const
{
    Vector_size results;
    find_helper(results, m_items, items);
    return results;
}

//REPLACE

template<typename STDContainer>
template<typename T1, typename T2, typename = if_container_predicate1_value<T1>, typename = if_container_value<T2>>
void Container<STDContainer>::replace(T1&& oldItems, T2&& newItems)
{
    replace_helper(m_items, std::forward<T1>(oldItems), std::forward<T2>(newItems));
}

template<typename STDContainer>
template<typename T, typename = if_container_value<T>>
void Container<STDContainer>::replace(const ThisInit& oldItems, T&& newItems)
{
    replace_helper(m_items, oldItems, std::forward<T>(newItems));
}

template<typename STDContainer>
template<typename T, typename = if_container_predicate1_value<T>>
void Container<STDContainer>::replace(T&& oldItems, const ThisInit& newItems)
{
    replace_helper(m_items, std::forward<T>(oldItems), newItems);
}

template<typename STDContainer>
void Container<STDContainer>::replace(const ThisInit& oldItems, const ThisInit& newItems)
{
    replace_helper(m_items, oldItems, newItems);
}

//SORT

template<typename STDContainer>
template<typename T, typename = if_predicate2<T>>
void Container<STDContainer>::sort(T&& predicate)
{
    sort_helper(m_items, std::forward<T>(predicate));
}

template<typename STDContainer>
void Container<STDContainer>::sort()
{
    sort_helper(m_items, std::less<>());
}

//IS SORTED

template<typename STDContainer>
template<typename T, typename = if_predicate2<T>>
bool Container<STDContainer>::isSorted(T&& predicate) const
{
    return is_sorted_helper(m_items, std::forward<T>(predicate));
}

template<typename STDContainer>
bool Container<STDContainer>::isSorted() const
{
    return is_sorted_helper(m_items, std::less<>());
}

//UNIQUE

template<typename STDContainer>
template<typename T, typename = if_predicate2<T>>
void Container<STDContainer>::unique(T&& predicate)
{
    unique_helper(m_items, std::forward<T>(predicate));
}

template<typename STDContainer>
void Container<STDContainer>::unique()
{
    unique_helper(m_items, std::equal_to<>());
}

//SHUFFLE

template<typename STDContainer>
void Container<STDContainer>::shuffle()
{
    shuffle_helper(m_items);
}

//REVERSE

template<typename STDContainer>
void Container<STDContainer>::reverse()
{
    reverse_helper(m_items);
}

//RESIZE

template<typename STDContainer>
inline void Container<STDContainer>::resize(size_t size)
{
    m_items.resize(size);
}

//RESERVE

template<typename STDContainer>
inline void Container<STDContainer>::reserve(size_t size)
{
    reserve_helper(m_items, size);
}

//CLEAR

template<typename STDContainer>
void Container<STDContainer>::clear()
{
    m_items.clear();
}

//SUB

template<typename STDContainer>
Container<STDContainer> Container<STDContainer>::sub(size_t index, size_t size) const
{
    return sub_helper<STDContainer>(m_items, index, size);
}

//TO CONTAINERS

template<typename STDContainer>
auto Container<STDContainer>::toStdVector() const -> vector_value
{
    return sub_helper<vector_value>(m_items);
}

template<typename STDContainer>
auto Container<STDContainer>::toStdVector(size_t index, size_t size) const -> vector_value
{
    return sub_helper<vector_value>(m_items, index, size);
}

template<typename STDContainer>
auto Container<STDContainer>::toStdList() const -> list_value
{
    return sub_helper<list_value>(m_items);
}

template<typename STDContainer>
auto Container<STDContainer>::toStdList(size_t index, size_t size) const -> list_value
{
    return sub_helper<list_value>(m_items, index, size);
}

template<typename STDContainer>
auto Container<STDContainer>::toStdDeque() const -> deque_value
{
    return sub_helper<deque_value>(m_items);
}

template<typename STDContainer>
auto Container<STDContainer>::toStdDeque(size_t index, size_t size) const -> deque_value
{
    return sub_helper<deque_value>(m_items, index, size);
}

template<typename STDContainer>
inline std::string Container<STDContainer>::toStdString() const
{
    return m_items;
}

template<>
inline std::string Container<std::string>::toStdString(size_t index, size_t size) const
{
    return m_items.substr(index, size);
}

//AS NATIVE STD

template<typename STDContainer>
inline STDContainer& Container<STDContainer>::asStd()
{
    return m_items;
}

template<typename STDContainer>
inline const STDContainer& Container<STDContainer>::asStd() const
{
    return m_items;
}

//ROTATE

template<typename STDContainer>
void Container<STDContainer>::rotateLeft(size_t count)
{
    std::rotate(m_items.begin(), std::next(m_items.begin(), count %= size()), m_items.end());
}

template<typename STDContainer>
void Container<STDContainer>::rotateRight(size_t count)
{
    std::rotate(m_items.rbegin(), std::next(m_items.rbegin(), count %= size()), m_items.rend());
}

//MERGE

template<typename STDContainer>
template<typename T, typename = if_container_value<T>>
void Container<STDContainer>::merge(T&& items)
{
    merge_helper(m_items, std::forward<T>(items), std::less<>());
}

template<typename STDContainer>
void Container<STDContainer>::merge(const ThisInit& items)
{
    merge_helper(m_items, items, std::less<>());
}

template<>
void Container<std::string>::merge(const char* text)
{
    merge_helper(m_items, StringWrapper(text), std::less<>());
}

template<typename STDContainer>
template<typename T1, typename T2, typename = if_container_value<T1>, typename = if_predicate2<T2>>
void Container<STDContainer>::merge(T1&& items, T2&& predicate)
{
    merge_helper(m_items, std::forward<T1>(items), std::forward<T2>(predicate));
}

template<typename STDContainer>
template<typename T, typename = if_predicate2<T>>
void Container<STDContainer>::merge(const ThisInit& items, T&& predicate)
{
    merge_helper(m_items, items, std::forward<T>(predicate));
}

template<>
template<typename T, typename = if_predicate2<T>>
void Container<std::string>::merge(const char* text, T&& predicate)
{
    merge_helper(m_items, StringWrapper(text), std::forward<T>(predicate));
}


///////////////////////////helpers///////////////////////////////

//ASSIGN HELPER

template<typename STDContainer>
template<typename T>
void Container<STDContainer>::assign_helper(ThisContainer& container, T&& items)
{
    assign_helper2(container, std::forward<T>(items), is_this_class<T>());
}

template<typename STDContainer>
template<typename T> //this class
void Container<STDContainer>::assign_helper2(ThisContainer& container, T&& items, boolean_true)
{
    container = std::forward<T>(items).m_items;
}

template<typename STDContainer>
template<typename T> //this class
void Container<STDContainer>::assign_helper2(ThisContainer& container, T&& items, boolean_false)
{
    assign_helper3(container, std::forward<T>(items), is_this_container<T>());
}

template<typename STDContainer>
template<typename T> //this container
void Container<STDContainer>::assign_helper3(ThisContainer& container, T&& items, boolean_true)
{
    container = std::forward<T>(items);
}

template<typename STDContainer>
template<typename T> //this container
void Container<STDContainer>::assign_helper3(ThisContainer& container, T&& items, boolean_false)
{
    assign_helper4(container, std::forward<T>(items), is_this_init<T>());
}

template<typename STDContainer>
template<typename T> //this init
void Container<STDContainer>::assign_helper4(ThisContainer& container, T&& items, boolean_true)
{
    container.assign(std::forward<T>(items));
}

template<typename STDContainer>
template<typename T> //any container
void Container<STDContainer>::assign_helper4(ThisContainer& container, T&& items, boolean_false)
{
    container.assign(items.cbegin(), items.cend());
}

//EQUAL HELPER

template<typename STDContainer>
template<typename T>
bool Container<STDContainer>::equal_helper(const ThisContainer& container, T&& items)
{
    return equal_helper2(container, std::forward<T>(items), is_this_class<T>());
}

template<typename STDContainer>
template<typename T> //this class
bool Container<STDContainer>::equal_helper2(const ThisContainer& container, T&& items, boolean_true)
{
    return container == items.m_items;
}

template<typename STDContainer>
template<typename T> //this class
bool Container<STDContainer>::equal_helper2(const ThisContainer& container, T&& items, boolean_false)
{
    return equal_helper3(container, std::forward<T>(items), is_this_container<T>());
}

template<typename STDContainer>
template<typename T> //this container
bool Container<STDContainer>::equal_helper3(const ThisContainer& container, T&& items, boolean_true)
{
    return container == items;
}

template<typename STDContainer>
template<typename T> //this container
bool Container<STDContainer>::equal_helper3(const ThisContainer& container, T&& items, boolean_false)
{
    return true;// equal_helper4(container, std::forward<T>(items), is_value_type<T>());
}

template<typename STDContainer>
bool Container<STDContainer>::equal_helper4(const ThisContainer& container, const value_type& items, boolean_true)
{
    return !container.empty() && std::next(container.begin(), 1) == container.end() && *container.begin() == items;
}

template<typename STDContainer>
template<typename T> //any container
bool Container<STDContainer>::equal_helper4(const ThisContainer& container, T&& items, boolean_false)
{
    return std::equal(container.begin(), container.end(), items.cbegin(), items.cend());
}

//INSERT HELPER

template<typename STDContainer>
template<typename T>
auto Container<STDContainer>::insert_helper(ThisContainer& container, const_iterator it, T&& items) -> iterator
{
    return insert_helper2(container, it, std::forward<T>(items), is_container<T>());
}

template<typename STDContainer>
template<typename T> //is_container
auto Container<STDContainer>::insert_helper2(ThisContainer& container, const_iterator it, T&& items, boolean_true) -> iterator
{
    return iterator();// container.insert(it, items.cbegin(), items.cend());
}

template<typename STDContainer>
template<typename T> //value_type
auto Container<STDContainer>::insert_helper2(ThisContainer& container, const_iterator it, T&& items, boolean_false) -> iterator
{
    return container.insert(it, std::forward<T>(items));
}

//FIND HELPER

template<typename STDContainer>
template<typename T>
void Container<STDContainer>::find_helper(size_t& result, const ThisContainer& ñontainer, T&& items)
{
    auto it = find_helper2(ñontainer.cbegin(), ñontainer.cend(), std::forward<T>(items));
    result = it != ñontainer.cend() ? std::distance(ñontainer.cbegin(), it) : NOT_FOUND;
}

template<typename STDContainer>
template<typename T>
void Container<STDContainer>::find_helper(Vector_size& results, const ThisContainer& container, T&& items)
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

template<typename STDContainer>
template<typename T>
auto Container<STDContainer>::find_helper2(const_iterator begin, const_iterator end, T&& items) -> const_iterator
{
    return find_helper3(begin, end, std::forward<T>(items), is_value_type<T>());
}

template<typename STDContainer>
auto Container<STDContainer>::find_helper3(const_iterator begin, const_iterator end, const value_type& item, boolean_true) -> const_iterator
{
    return std::find(begin, end, item);
}

template<typename STDContainer>
template<typename T> //value_type
auto Container<STDContainer>::find_helper3(const_iterator begin, const_iterator end, T&& items, boolean_false) -> const_iterator
{
    return find_helper4(begin, end, std::forward<T>(items), is_predicate1<T>());
}

template<typename STDContainer>
template<typename T> //predicate1
auto Container<STDContainer>::find_helper4(const_iterator begin, const_iterator end, T&& predicate, boolean_true) -> const_iterator
{
    return std::find_if(begin, end, std::forward<T>(predicate));
}

template<typename STDContainer>
template<typename T> //container
auto Container<STDContainer>::find_helper4(const_iterator begin, const_iterator end, T&& items, boolean_false) -> const_iterator
{
    std::search
    return empty_helper(items) ? end : std::search(begin, end, items.cbegin(), items.cend());
}

//REMOVE HELPER

template<typename STDContainer>
template<typename T1, typename T2>
void Container<STDContainer>::remove_helper(T1& container, T2&& items)
{
    remove_helper2(container, items, is_value_type<T2>());
}

template<typename STDContainer>
template<typename T> //value_type
void Container<STDContainer>::remove_helper2(T& container, const value_type& items, boolean_true)
{
    container.erase(std::remove(container.begin(), container.end(), items), container.end());
}

template<typename STDContainer>
void Container<STDContainer>::remove_helper2(list_value& container, const value_type& items, boolean_true)
{
    container.remove(items);
}

template<typename STDContainer>
template<typename T1, typename T2> //value_type
void Container<STDContainer>::remove_helper2(T1& container, T2&& items, boolean_false)
{
    remove_helper3(container, items, is_predicate1<T2>());
}

template<typename STDContainer>
template<typename T1, typename T2> //predicate1
void Container<STDContainer>::remove_helper3(T1& container, T2&& predicate, boolean_true)
{
    container.erase(std::remove_if(container.begin(), container.end(), predicate), container.end());
}

template<typename STDContainer>
template<typename T> //predicate1
void Container<STDContainer>::remove_helper3(list_value& container, T&& predicate, boolean_true)
{
    container.remove_if(predicate);
}

template<typename STDContainer>
template<typename T1, typename T2> //container
void Container<STDContainer>::remove_helper3(T1& container, T2&& items, boolean_false)
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

template<typename STDContainer>
void Container<STDContainer>::erase_helper(ThisContainer& container, size_t index, size_t size)
{
    if (size && index + size <= container.size())
    {
        auto it = std::next(container.begin(), index);
        container.erase(it, std::next(it, size));
    }
}

//REPLACE HELPER

template<typename STDContainer>
template<typename T1, typename T2>
void Container<STDContainer>::replace_helper(ThisContainer& container, T1&& oldItems, T2&& newItems)
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
            reserve_helper(container, size);
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

template<typename STDContainer>
template<typename T, typename Predicate>
void Container<STDContainer>::sort_helper(T&& container, Predicate&& predicate)
{
    std::sort(container.begin(), container.end(), predicate);
}

template<typename STDContainer>
template<typename Predicate>
void Container<STDContainer>::sort_helper(list_value& container, Predicate&& predicate)
{
    container.sort(predicate);
}

//IS SORTED HELPER

template<typename STDContainer>
template<typename Predicate>
bool Container<STDContainer>::is_sorted_helper(const ThisContainer& container, Predicate&& predicate)
{
    return std::is_sorted(container.begin(), container.end(), predicate);
}

//UNIQUE HELPER

template<typename STDContainer>
template<typename T, typename Predicate>
void Container<STDContainer>::unique_helper(T&& container, Predicate&& predicate)
{
    container.erase(std::unique(container.begin(), container.end(), std::forward<Predicate>(predicate)), container.end());
}

template<typename STDContainer>
template<typename Predicate>
void Container<STDContainer>::unique_helper(list_value& container, Predicate&& predicate)
{
    container.unique(std::forward<Predicate>(predicate));
}

//SHUFFLE HELPER

template<typename STDContainer>
template<typename T>
void Container<STDContainer>::shuffle_helper(T&& container)
{
    std::shuffle(container.begin(), container.end(), std::mt19937(time(0)));
}

template<typename STDContainer>
void Container<STDContainer>::shuffle_helper(list_value& container)
{
    std::vector<std::reference_wrapper<value_type>> temp(container.begin(), container.end());
    shuffle_helper(temp);
    container = list_value(temp.begin(), temp.end());
}

//REVERSE HELPER

template<typename STDContainer>
template<typename T>
void Container<STDContainer>::reverse_helper(T&& container)
{
    std::reverse(container.begin(), container.end());
}

template<typename STDContainer>
void Container<STDContainer>::reverse_helper(list_value& container)
{
    container.reverse();
}

//RESERVE HELPER

template<typename STDContainer>
template<typename T>
inline void Container<STDContainer>::reserve_helper(T&&, size_t)
{}

template<typename STDContainer>
inline void Container<STDContainer>::reserve_helper(vector_value& vector, size_t size)
{
    vector.reserve(size);
}

template<typename STDContainer>
inline void Container<STDContainer>::reserve_helper(std::string& string, size_t size)
{
    string.reserve(size);
}

//SUB HELPER

template<typename STDContainer>
template<typename T>
Container<T> Container<STDContainer>::sub_helper(const ThisContainer& container)
{
    return Container<T>(T(container.begin(), container.end()));
}

template<typename STDContainer>
template<typename T>
Container<T> Container<STDContainer>::sub_helper(const ThisContainer& container, size_t index, size_t size)
{
    if (size && index + size <= container.size())
    {
        auto start = std::next(container.begin(), index);
        return Container<T>(T(start, std::next(start, size)));
    }
    return Container<T>();
}

//MERGE HELPER

template<typename STDContainer>
template<typename T, typename Predicate>
void Container<STDContainer>::merge_helper(ThisContainer& container, T&& items, Predicate&& predicate)
{
    return merge_helper2(container, std::forward<T>(items), std::forward<Predicate>(predicate), is_value_type<T>());
}

template<typename STDContainer>
template<typename T, typename Predicate> //this class
void Container<STDContainer>::merge_helper2(ThisContainer& container, T&& items, Predicate&& predicate, boolean_true)
{
    merge_helper3(container, &items, &items + 1, std::forward<Predicate>(predicate));
}

template<typename STDContainer>
template<typename T, typename Predicate> //any container
void Container<STDContainer>::merge_helper2(ThisContainer& container, T&& items, Predicate&& predicate, boolean_false)
{
    merge_helper3(container, items.cbegin(), items.cend(), std::forward<Predicate>(predicate));
}

template<typename STDContainer>
template<typename T, typename Predicate>
void Container<STDContainer>::merge_helper3(ThisContainer& container, T&& begin, T&& end, Predicate&& predicate)
{
    ThisContainer temp;
    std::merge(container.begin(), container.end(), begin, end, std::back_inserter(temp), std::forward<Predicate>(predicate));
    container = std::move(temp);
}

//EMPTY HELPER

template<typename STDContainer>
template<typename T>
constexpr bool Container<STDContainer>::empty_helper(T&& items)
{
    return true;// empty_helper2(items, is_container<T>());
}

template<typename STDContainer>
template<typename T> //container
constexpr bool Container<STDContainer>::empty_helper2(T&& items, boolean_true)
{
    return false;// std::empty(items);
}

template<typename STDContainer>
template<typename T> //container
constexpr bool Container<STDContainer>::empty_helper2(T&& items, boolean_false)
{
    return false;
}

//SIZE HELPER

template<typename STDContainer>
template<typename T>
constexpr size_t Container<STDContainer>::size_helper(T&& items)
{
    return 0;// size_helper2(items, is_container<T>());
}

template<typename STDContainer>
template<typename T> //container
constexpr size_t Container<STDContainer>::size_helper2(T&& items, boolean_true)
{
    return items.size();
}

template<typename STDContainer>
template<typename T> //not container
constexpr size_t Container<STDContainer>::size_helper2(T&& items, boolean_false)
{
    return 1;
}

#pragma warning(pop)

} // namespace dpg