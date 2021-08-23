#pragma once
#include "sfinae.h"
#include <type_traits>

template<typename Container, typename Source>
void assign(Container& container, Source&& source)
{
}