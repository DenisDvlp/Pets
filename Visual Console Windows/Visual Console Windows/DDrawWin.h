//DDrawWin.h
#pragma once
#include "DDrawT.h"
#include "DTypes.h"

struct _CHAR_INFO;

class DDrawWin
    : public DDrawT<_CHAR_INFO, dint, dint>
{
public:
    void  fill(const DColor) override;
    void  drawRect(const DRect&, const DColor) override;
    void  drawText(const DRect&, const DString&, const DColor, const DAlign = DAlign::DEFAULT) override;
    void  drawText(const DRect&, const DStringList&, const DColor, const DAlign = DAlign::DEFAULT) override;
    DRect calcTextRect(const DString&) override;
    DRect calcTextRect(const DStringList&) override;
};