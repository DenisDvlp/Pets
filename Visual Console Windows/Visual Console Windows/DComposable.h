//DComposable.h
#pragma once
#include "DVector.h"

class DComposable
{
public:
    explicit DComposable(DComposable* = nullptr);
    virtual ~DComposable();
    virtual void addChild(DComposable*);
    virtual void removeChild(DComposable*);
    void setParent(DComposable*);
    void bringToFront();
    void sendToBack();
    const DVector<DComposable*>& children();
    size_t childrenCount();
    DComposable* parent();
protected:
    DComposable* m_parent = nullptr;
    DVector<DComposable*> m_children;
};

