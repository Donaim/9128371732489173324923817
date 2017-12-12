#pragma once

#include "setSize.cpp"
#include "set.h"
#include "fset.h"
#include "orderedset.h"

class KartesianProduct : public virtual Set {
protected:
    KartesianProduct(int pairLen) : PairSize(pairLen, false, false, 1) {}
public:
    const Cardinality PairSize;
};

class ISetCollection {
protected:
    static const Set** createPair(const Set &a, const Set &b){
        const Set** re = new const Set*[2];
        re[0] = &a;
        re[1] = &b;
        return re;
    }

public:
    const Set** const list;
    ISetCollection(const Set** l) : list(l) {}
};

class FunctionalKartesianSet : public virtual FunctionalSet, public virtual KartesianProduct, public virtual ISetCollection {
public:
    FunctionalKartesianSet(const Set** list, const int size);
    bool Contains(const Element& e) const override ;
};

class FiniteKartesianPSet : public virtual FiniteSet, public virtual KartesianProduct, public virtual ISetCollection {
private:
    FiniteKartesianPSet(const FiniteSet &kProduct, const Set &a, const Set &b)
    : FiniteSet(kProduct), KartesianProduct(2), ISizeable(kProduct.Size), ISetCollection(ISetCollection::createPair(a, b))
     {}
public:
    FiniteKartesianPSet(const FiniteSet &a, const FiniteSet &b) : FiniteKartesianPSet(product(a, b), a, b) {}
public:
    static const FiniteSet& product(const FiniteSet& a, const FiniteSet& b) ;
};