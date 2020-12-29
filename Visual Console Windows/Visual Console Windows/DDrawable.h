//DDrawable.h
#pragma once
#include "IDDrawable.h"

class DDrawable
    : public IDDrawable
{
public:
    void draw(IDDraw&) const override;
};