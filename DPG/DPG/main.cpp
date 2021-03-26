#include "dpg_container2.h"
#include <type_traits>
#include <iostream>

using Vec = DContainerT<std::vector<int>>;
using List = DContainerT<std::list<size_t>>;
using Deq = DContainerT<std::deque<short>>;
using Str = DContainerT<std::string>;

template<typename T>
void init()
{
    Vec v = { 'd','f' };
    List l = { 2, 9 };
    Deq d = { 2, 9 };
    Str s = "dsf";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    int arr[] = { 3,5,6 };
    char arr1[] = "123";
    int *p = arr;
    char*p1 = arr1;

    T t21 = v;
    T t22 = l;
    T t23 = d;
    T t24 = s;
    T t1 = cll;
    T t2 = cvv;
    T t3 = cdd;
    T t4 = css;
    T t5 = ll;
    T t6 = vv;
    T t7 = dd;
    T t8 = ss;
    T t9 = "123";
    T t10 = arr;
    T t11 = arr1;
    T t12 = p1;
    T t13{ p , 3 };
    T t14( p , 3 );
    T t15 = { 3 , 3 };
    T t16(10);
    T t17(10);
}

template<typename T>
void checkPop(T&& t)
{
    Vec v = { 'd','f' };
    List l = { 2, 9 };
    Deq d = { 2, 9 };
    Str s = "dsf";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    int arr[] = { 3,5,6 };
    char arr1[] = "123";
    int* p = arr;
    char* p1 = arr1;

    t.push(v);
    t.push(l);
    t.push(d);
    t.push(s);
    t.push(cll);
    t.push(cvv);
    t.push(cdd);
    t.push(css);
    t.push(ll);
    t.push(vv);
    t.push(dd);
    t.push(ss);
    t.push("345");
    t.push('g');
    t.push({ 'd','f' });
    t.push({ 2ll, 4ll });
    t.push({ 3l, 5l });
    t.push(ss.begin(), ss.end());
    t.push(cll.cbegin(), cll.cend());
    t.push(d.rbegin(), d.rend());
    t.push(arr);
    t.push(arr1);
    t.push(p, 3);
    t.push(p1);
}

template<typename T>
void checkFront(T&& t)
{
    Vec v = { 'd','f' };
    List l = { 2, 9 };
    Deq d = { 2, 9 };
    Str s = "dsf";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    int arr[] = { 3,5,6 };
    char arr1[] = "123";
    int* p = arr;
    char* p1 = arr1;

    t.front(v);
    t.front(l);
    t.front(d);
    t.front(s);
    t.front(cll);
    t.front(cvv);
    t.front(cdd);
    t.front(css);
    t.front(ll);
    t.front(vv);
    t.front(dd);
    t.front(ss);
    t.front("345");
    t.front('g');
    t.front({ 'd','f' });
    t.front({ 2ll, 4ll });
    t.front({ 3l, 5l });
    t.front(ss.begin(), ss.end());
    t.front(cll.cbegin(), cll.cend());
    t.front(d.rbegin(), d.rend());
    t.front(arr);
    t.front(arr1);
    t.front(p, 3);
    t.front(p1);
}

template<typename T>
void checkShiftLeft(T&& t)
{
    Vec v = { 'd','f' };
    List l = { 2, 9 };
    Deq d = { 2, 9 };
    Str s = "dsf";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    int arr[] = { 3,5,6 };
    char arr1[] = "123";
    char* p1 = arr1;

    t << v
        << l
        << d
        << s
        << cll
        << cvv
        << cdd
        << css
        << ll
        << vv
        << dd
        << ss
        << arr
        << arr1
        << p1
        << "345"
        << 'g';
}

template<typename T>
void checkAssign(T&& t)
{
    Vec v = { 'd','f' };
    List l = { 2, 9 };
    Deq d = { 2, 9 };
    Str s = "dsf";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    int arr[] = { 3,5,6 };
    char arr1[] = "123";
    int* p = arr;
    char* p1 = arr1;

    t.assign(v);
    t.assign(l);
    t.assign(d);
    t.assign(s);
    t.assign(cll);
    t.assign(cvv);
    t.assign(cdd);
    t.assign(css);
    t.assign(ll);
    t.assign(vv);
    t.assign(dd);
    t.assign(ss);
    t.assign("345");
    t.assign({ 'd','f' });
    t.assign({ 2ll, 4ll });
    t.assign({ 3l, 5l });
    t.assign(ss.begin(), ss.end());
    t.assign(cll.cbegin(), cll.cend());
    t.assign(d.rbegin(), d.rend());
    t.assign(arr);
    t.assign(arr1);
    t.assign(p, 3);
    t.assign(p1);
}

template<typename T>
void checkAssign2(T&& t)
{
    Vec v = { 'd','f' };
    List l = { 2, 9 };
    Deq d = { 2, 9 };
    Str s = "dsf";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    t = v;
    t = l;
    t = d;
    t = s;
    t = cll;
    t = cvv;
    t = cdd;
    t = css;
    t = ll;
    t = vv;
    t = dd;
    t = ss;
    t = "345";
    t = { 'd','f' };
    t = { 2ll, 4ll };
    t = { 3l, 5l };
}

template<typename T>
void checkAdd(T&& t)
{
    Vec v = { 'd','f' };
    List l = { 2, 9 };
    Deq d = { 2, 9 };
    Str s = "dsf";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    t += v;
    t += l;
    t += d;
    t += s;
    t += cll;
    t += cvv;
    t += cdd;
    t += css;
    t += ll;
    t += vv;
    t += dd;
    t += ss;
    t += "345";
    t += 'h';
    t += { 'd', 'f' };
    t += { 2ll, 4ll };
    t += { 3l, 5l };
}

template<typename T>
void checkPlus(T&& t)
{
    Vec v = { 'd','f' };
    List l = { 2, 9 };
    Deq d = { 2, 9 };
    Str s = "dsf";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    t + v;
    t + l;
    t + d;
    t + s;
    t + cll;
    t + cvv;
    t + cdd;
    t + css;
    t + ll;
    t + vv;
    t + dd;
    t + ss;
    t + "345";
    t + 'h';
}

template<typename T>
void checkEqual(T&& t)
{
    Vec v = { 'd','f' };
    List l = { 2, 9 };
    Deq d = { 2, 9 };
    Str s = "dsf";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    t == v;
    t == l;
    t == d;
    t == s;
    t == cll;
    t == cvv;
    t == cdd;
    t == css;
    t == ll;
    t == vv;
    t == dd;
    t == ss;
    t == "345";
}

template<typename T>
void checkEqual2(T&& t)
{
    Vec v = { 'd','f' };
    List l = { 2, 9 };
    Deq d = { 2, 9 };
    Str s = "dsf";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    v == t;
    l == t;
    d == t;
    s == t;
    cll == t;
    cvv == t;
    cdd == t;
    css == t;
    ll == t;
    vv == t;
    dd == t;
    ss == t;
    "3t:" == t;
}

template<typename T>
void checkNEqual(T&& t)
{
    Vec v = { 'd','f' };
    List l = { 2, 9 };
    Deq d = { 2, 9 };
    Str s = "dsf";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    t != v;
    t != l;
    t != d;
    t != s;
    t != cll;
    t != cvv;
    t != cdd;
    t != css;
    t != ll;
    t != vv;
    t != dd;
    t != ss;
    t != "345";
}

template<typename T>
void checkNEqual2(T&& t)
{
    Vec v = { 'd','f' };
    List l = { 2, 9 };
    Deq d = { 2, 9 };
    Str s = "dsf";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    v != t;
    l != t;
    d != t;
    s != t;
    cll != t;
    cvv != t;
    cdd != t;
    css != t;
    ll != t;
    vv != t;
    dd != t;
    ss != t;
    "3t:" != t;
}

template<typename T>
void checkAccess(T&& t)
{
    pure<T> t1(2);
    const pure<T> t2(2);
    t1[0];
    t2[0];
}

template<typename Iter>
void f(Iter begin, Iter end)
{
    if (has_method_base<Iter>)
    {
        auto it = begin.base();
        auto it2 = end.base();
    }
}

template<typename T>
void checkErase(T&& t)
{
    t.erase(0);
    t.erase(t.rbegin());
    t.erase(0, 1);
    t.erase(--t.end());
    t.erase(--t.cend());
    t.erase(t.rbegin(), --t.rend());
    t.erase(t.crbegin(), t.crend());
}

template<typename T>
void checkInsert(T&& t)
{
    Vec v = { 'd','f' };
    List l = { 2, 9 };
    Deq d = { 2, 9 };
    Str s = "dsf";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    int arr[] = { 3,5,6 };
    char arr1[] = "123";
    int* p = arr;
    char* p1 = arr1;

    t.insert(++t.begin(), v);
    t.insert(++t.begin(), l);
    t.insert(++t.begin(), d);
    t.insert(++t.begin(), s);
    t.insert(++t.begin(), cll);
    t.insert(++t.begin(), cvv);
    t.insert(++t.begin(), cdd);
    t.insert(++t.begin(), css);
    t.insert(++t.begin(), ll);
    t.insert(++t.begin(), vv);
    t.insert(++t.begin(), dd);
    t.insert(++t.begin(), ss);
    t.insert(++t.begin(), "345");
    t.insert(++t.begin(), { 'd','f' });
    t.insert(++t.begin(), { 2ll, 4ll });
    t.insert(++t.begin(), { 3l, 5l });
    t.insert(++t.begin(), ss.begin(), ss.end());
    t.insert(++t.begin(), cll.cbegin(), cll.cend());
    t.insert(++t.begin(), d.rbegin(), d.rend());
    t.insert(++t.begin(), arr);
    t.insert(++t.begin(), arr1);
    t.insert(++t.begin(), p, 3);
    t.insert(++t.begin(), p1);

    t.insert(1, v);
    t.insert(1, l);
    t.insert(1, d);
    t.insert(1, s);
    t.insert(1, cll);
    t.insert(1, cvv);
    t.insert(1, cdd);
    t.insert(1, css);
    t.insert(1, ll);
    t.insert(1, vv);
    t.insert(1, dd);
    t.insert(1, ss);
    t.insert(1, "345");
    t.insert(1, { 'd','f' });
    t.insert(1, { 2ll, 4ll });
    t.insert(1, { 3l, 5l });
    t.insert(1, ss.begin(), ss.end());
    t.insert(1, cll.cbegin(), cll.cend());
    t.insert(1, d.rbegin(), d.rend());
    t.insert(1, arr);
    t.insert(1, arr1);
    t.insert(1, p, 3);
    t.insert(1, p1);
    t.insert(1, arr, 1);
}

template<typename T>
void checkEmplace(T&& t)
{
    t.emplace_insert(t.begin(), '3');
    t.emplace_insert(++t.begin(), 45);
    t.emplace_insert(++t.begin(), 5ll);
    t.emplace_insert(1, '3');
    t.emplace_insert(1, 45);
    t.emplace_insert(1, 5ll);
}

template<typename T>
void checkEmplacePush(T&& t)
{
    t.emplace_push('3');
    t.emplace_push(45);
    t.emplace_push(5ll);
    t.emplace_push('3');
    t.emplace_push(45);
    t.emplace_push(5ll);
}

template<typename T>
void checkEmplaceFront(T&& t)
{
    t.emplace_front('3');
    t.emplace_front(45);
    t.emplace_front(5ll);
    t.emplace_front('3');
    t.emplace_front(45);
    t.emplace_front(5ll);
}

template<typename T>
void checkFind(T&& t)
{
    Vec v = { '3',char(45) };
    List l = { 45, 5 };
    Deq d = { 45, 5 };
    Str s = "3\5";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    int arr[] = { 51,5,6 };
    char arr1[] = "123";
    int* p = arr;
    char* p1 = arr1;

    auto it = t.find('8');
    it = t.find(45);
    it = t.find(5ll);
    it = t.find("34");
    auto is = it == t.cend();
    it = t.find([](const auto& value) {return value == '3'; });
    it = t.find([](const auto& value) {return value == 45; });
    it = t.find([](const auto& value) {return value == 5ll; });

    it = t.find(v);
    it = t.find(l);
    it = t.find(d);
    it = t.find(s);
    it = t.find(vv);
    it = t.find(ll);
    it = t.find(dd);
    it = t.find(ss);
    it = t.find(cvv);
    it = t.find(cll);
    it = t.find(cdd);
    it = t.find(css);
    t.find(arr);
    t.find(arr1);
    it = t.find(arr, 2, std::equal_to<>());
    it = t.find(p1, 2);
    it = t.find(d.rbegin(), d.rend(), 
        [](const auto& v, const auto& v2) {return v == v2; });
}

template<typename T>
void checkFindAll(T&& t)
{
    Vec v = { '3',char(45) };
    List l = { 45, 5 };
    Deq d = { 45, 5 };
    Str s = "3\5";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    int arr[] = { 51,5,6 };
    char arr1[] = "123";
    int* p = arr;
    char* p1 = arr1;

    auto it = t.find_all('8');
    it = t.find_all(45);
    it = t.find_all(5ll);
    it = t.find_all("34");
    it = t.find_all([](const auto& value) {return value == '3'; });
    it = t.find_all([](const auto& value) {return value == 45; });
    it = t.find_all([](const auto& value) {return value == 5ll; });

    it = t.find_all(v);
    it = t.find_all(l);
    it = t.find_all(d);
    it = t.find_all(s);
    it = t.find_all(vv);
    it = t.find_all(ll);
    it = t.find_all(dd);
    it = t.find_all(ss);
    it = t.find_all(cvv);
    it = t.find_all(cll);
    it = t.find_all(cdd);
    it = t.find_all(css);
    t.find_all(arr);
    t.find_all(arr1);
    it = t.find_all(arr, 2, std::equal_to<>());
    it = t.find_all(p1, 2);
    it = t.find_all(d.rbegin(), d.rend(), 
        [](const auto& v, const auto& v2) {return v == v2; });
}

template<typename T>
void checkOperations(T&& t)
{
    t.shrink();
    t.sort();
    t.sort(std::less<>());
    t.reverse();
    t.shuffle();
    t.release();
}

template<typename T>
void checkReplace(T&& t)
{
    Vec v = { '3',char(45) };
    List l = { 45, 5 };
    Deq d = { 45, 5 };
    Str s = "3\5";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    int arr[] = { 51,5,6 };
    char arr1[] = "123";
    int* p = arr;
    char* p1 = arr1;

    t.replace('3', 54);
    t.replace(arr, arr1, std::less<>());
    t.replace('3', arr1);
    t.replace(p1, 54, std::less<>());
    t.replace('3', dd);
    t.replace({51}, ss, std::less<>());
    t.replace({ 51 }, s.begin(), s.end());
    t.replace(cll.rbegin(), cll.rend(), cvv, std::less<>());
    t.replace(cdd, cvv);
    t.replace(css, cll, std::less<>());
    t.replace(cdd, cvv);
    t.replace(css, cll, std::less<>());
    t.replace(v, l);
    t.replace(d, cll, std::less<>());
    t.replace(l, arr1);
    t.replace(l, s, std::less<>());
    t.replace(d, arr1);
    t.replace(l, s, [](auto& a, auto& b) { return a == b; });
    t.replace(p, 2, 65);
    t.replace(v, arr1);
    t.replace("123", arr1, [](auto& a, auto& b) { return a == b; });
}

template<typename T>
void checkRemove(T&& t)
{
    Vec v = { '3',char(45) };
    List l = { 45, 5 };
    Deq d = { 45, 5 };
    Str s = "3\5";
    const std::list<short> cll(2, 5);
    const std::vector<long long> cvv(2, 5);
    const std::deque<int> cdd(2, 5);
    const std::string css = "123";
    std::list<int> ll(2, 5);
    std::vector<int> vv(2, 5);
    std::deque<size_t> dd(2, 5);
    std::string ss = "123";

    int arr[] = { 51,5,6 };
    char arr1[] = "123";
    int* p = arr;
    char* p1 = arr1;

    t.remove(54);
    t.remove(arr1, std::less<>());
    t.remove(arr1);
    t.remove(p1, 54, std::less<>());
    t.remove('3');
    t.remove(ss, std::less<>());
    t.remove({ 51 });
    t.remove(cll.rbegin(), cll.rend(), std::less<>());
    t.remove(cdd);
    t.remove(css, std::less<>());
    t.remove(cll);
    t.remove(cvv, std::less<>());
    t.remove(v);
    t.remove(d, std::less<>());
    t.remove(l);
    t.remove(l, std::less<>());
    t.remove(d);
    t.remove(p, 2);
    t.remove(s, [](auto& a, auto& b) { return a == b; });
    t.remove("123", [](auto& a, auto& b) { return a == b; });
}

template<typename T>
void test()
{
    T t;

    init<T>();
    checkPop(t);
    checkFront(t);
    checkShiftLeft(t);
    checkAssign(t);
    checkAssign2(t);
    checkAdd(t);
    checkPlus(t);
    checkEqual(t);
    checkEqual2(t);
    checkNEqual(t);
    checkNEqual2(t);
    checkAccess(t);
    checkInsert(t);
    checkErase(t);
    checkEmplace(t);
    checkEmplacePush(t);
    checkEmplaceFront(t);
    checkFind(t);
    checkFindAll(t);
    checkOperations(t);
    checkReplace(t);
    checkRemove(t);
}

int main()
{
    std::list<int> l;
    std::vector<int> v;
    test<Vec>();
    test<List>();
    test<Deq>();
    test<Str>();

    char arr[] = {'2','3'};
    std::string ss2 = "34";
    DContainerT<std::list<char>> s = "123456";

    s.push(ss2.begin(), ss2.end());
    auto r = s.split(ss2);
}