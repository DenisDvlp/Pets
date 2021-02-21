//DView.h
#pragma once
#include "DComposable.h"
#include "DShapeable.h"
#include "DDrawable.h"
#include "DMessages.h"

class DView
    : public DComposable<DView>
    , public DShapeable
    , public DDrawable
{
public:
    using DComposable<DView>::DComposable;
    virtual void onSystemMouseMove(const DMouseMessage&);
    virtual void onSystemMouseUp(const DMouseMessage&);
    virtual void onSystemMouseDown(const DMouseMessage&);
    virtual void onSystemKeyUp(Key);
    virtual void onSystemKeyDown(Key);
};

