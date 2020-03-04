//IDDrawT.h
#pragma once
#include "DAlign.h"
#include "DColor.h"
#include "DString.h"
#include "DStringList.h"
#include "DRect.h"

template<typename T>
class IDDrawT
{
public:
    virtual           ~IDDrawT() = default;
    virtual void      fill(const DColor) = 0;
    virtual void      drawRect(const DRectT<T>&, const DColor) = 0;
    virtual void      drawText(const DRectT<T>&, const DString&, const DColor, const DAlign = DAlign::DEFAULT) = 0;
    virtual void      drawText(const DRectT<T>&, const DStringList&, const DColor, const DAlign = DAlign::DEFAULT) = 0;
    virtual DRectT<T> calcTextRect(const DString&) = 0;
    virtual DRectT<T> calcTextRect(const DStringList&) = 0;
};