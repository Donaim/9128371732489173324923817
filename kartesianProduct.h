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

class FunctionalKartesianSet : public virtual FunctionalSet, public virtual KartesianProduct {
protected:
    const Set** list;
public:
    FunctionalKartesianSet(const Set** list, const int size);
    bool Contains(const Element& e) const override ;
};

class FiniteKartesianPSet : public virtual FiniteSet, public virtual KartesianProduct {
private:
    FiniteKartesianPSet(const FiniteSet &kProduct) : FiniteSet(kProduct), KartesianProduct(2), ISizeable(kProduct.Size) {}
public:
    FiniteKartesianPSet(const FiniteSet &a, const FiniteSet &b) : FiniteKartesianPSet(product(a, b)) {}
public:
    static const FiniteSet& product(const FiniteSet& a, const FiniteSet& b) ;
};