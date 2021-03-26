
#include <list>
#include <vector>
#include <forward_list>

struct MyCont
{
    using value_type = void;
    void operator()() {}
};

#include "sfinae_5v.cpp"

void ff() {}


int main()
{
    std::vector<int> v;
    std::list<int> l;
    std::forward_list<int> fl;
    MyCont mc;
    int x = 42;
    f(v);
    f(l);
    f(fl);
    f(mc);
    f(x);

    auto la = [] {};
    const  MyCont mc2;
    f2(la);
    f2(mc);
    f2(mc2);
    f2(ff);


}