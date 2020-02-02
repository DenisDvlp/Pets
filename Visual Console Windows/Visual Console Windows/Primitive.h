#pragma once
#include "Drawable.h"
#include "DString.h"

class Primitive :
    public Drawable
{
public:
    using Drawable::Drawable;
    Color color;
    Color textColor;
    Align textAlign;
    DString text;
private:
    void onDraw(IDraw*) override;
};

