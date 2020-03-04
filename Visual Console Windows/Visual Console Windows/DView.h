//DView.h
#pragma once
#include "DComposable.h"
#include "DShapeable.h"
#include "DDrawable.h"

class DView
    : public DComposable
    , public DShapeable
    , public DDrawable
{
};

