#pragma once
#include <iostream>

void intref(int&)
{
    std::cout << "&\n";
}

void intref(int&&)
{
    std::cout << "&&\n";
}

template<typename T>
void foo(T&& t)
{
    intref(t);
}