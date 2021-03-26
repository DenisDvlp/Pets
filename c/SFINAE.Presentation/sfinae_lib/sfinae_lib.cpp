#include "rref.h"
#include "assign.h"
#include "sfinae.h"
#include <vector>
#include <list>
#include <deque>
#include <string>

template<typename Container, typename Source>
void assign(Container& container, Source&& source);

int main()
{

    std::vector<char> v;
    std::list<int>    l;
    std::deque<short> d;
    std::string       s;

    assign(v, l);
    assign(v, d);
    assign(v, s);
    assign(l, v);
    assign(d, v);
    assign(s, v);

    std::vector<char> v2;
    assign(v, std::move(v2));
    assign(v, "qwerty");
    assign(v, 'r');
    assign(v, 32);
    assign(v, {1,2,3,4});

    assign(l, "qwerty");
    assign(l, 'r');
    assign(l, 32);

    assign(d, "qwerty");
    assign(d, 'r');
    assign(d, 32);

    int arr[123] = { 1,2,3 };
    assign(v, arr);

    const char* str = "qwerty";
    assign(v, str);

    char str2[] = "qwerty";
    assign(v, str2);

    std::cout << std::is_constructible_v<std::remove_extent_t<decltype(arr)>, int>;
}