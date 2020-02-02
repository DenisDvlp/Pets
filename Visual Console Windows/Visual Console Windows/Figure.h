// Figure.h
#pragma once
#include "Drawable.h"
#include "IDraw.h"

class Figure
    : public Drawable
{
public:
    using Drawable::Drawable;
    Color color;
private:
    void onDraw(IDraw*) override;
};

