//IDDrawable.h
#pragma once
#include "IDDraw.h"

class IDDrawable
{
public:
    virtual ~IDDrawable() = default;
    virtual void draw(IDDraw&) const = 0;
};