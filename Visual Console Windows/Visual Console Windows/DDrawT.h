//DDrawT.h
#pragma once
#include "IDDraw.h"
#include "DSizableT.h"
#include "BiArray.h"

template<typename P, typename D, typename S>
class DDrawT
    : public IDDraw<D>
    , public DSizableT<S>
{
public:
    P* buffer();
private:
    void resize(DSizeT<S>&) override;
protected:
    BiArray<P> m_biArray;
};

template<typename P, typename D, typename S>
P* DDrawT<P, D, S>::buffer()
{
    return m_biArray.raw();
}

template<typename P, typename D, typename S>
void DDrawT<P, D, S>::resize(DSizeT<S>& size)
{
    m_biArray.size(size);
}