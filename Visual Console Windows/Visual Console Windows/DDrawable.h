//DDrawable.h
#pragma once
#include "IDDrawable.h"

class DDrawable
    : public IDDrawable
{
public:
    void draw() const override;
};