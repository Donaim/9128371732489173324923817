#pragma once

#include "set.h"
#include "initializator.cpp"
#include <iostream>

class FiniteSet : public virtual Set, public IForAll, public IExists, public virtual IPrintable {
public:
    const Element** const list;
public:
    FiniteSet(const Element** es, int size);
    FiniteSet(Initial& v);

    bool Contains(const Element& e) const override;

    bool ForAll(const RulePtr& r) const override ;
    bool Exists(const RulePtr& r) const override ;

    Set& Union(const Set& b) const override ;
    Set& Intersect(const Set& b) const override ;
    Set& Substract(const Set& b) const override ;

    // const FiniteSet& KartesianProduct(const FiniteSet& o) const ;

    void Print(ostream& os) const override ;
};