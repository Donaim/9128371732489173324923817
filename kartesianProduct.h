#pragma once

#include "setSize.cpp"
#include "set.h"
#include "fset.h"
#include "orderedset.h"

class KartesianProduct : public virtual FunctionalSet {
protected:
    KartesianProduct(int pairLen) : PairSize(pairLen, false, false, 1) {}
public:
    const ISizeable PairSize;
};

class FunctionalKartesianSet : public virtual FunctionalSet, public virtual KartesianProduct {
protected:
    const Set** list;
public:
    FunctionalKartesianSet(const Set** list, const int size);
    bool Contains(const Element& e) const override ;
};