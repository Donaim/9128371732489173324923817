#pragma once

#include "set.h"
#include "initializator.cpp"
#include <iostream>

class FiniteSet : public Set, public virtual IForAll, public virtual IExists, public virtual IPrintable {
protected:
    const Element** const list;
public:
    FiniteSet(const Element** es, int size);
    FiniteSet(Initial& v);

    bool Contains(const Element& e) const override;

    bool ForAll(const RulePtr& r) const override ;
    bool Exists(const RulePtr& r) const override ;

    Set& Sum(const Set& b) const override ;
    Set& Intersect(const Set& b) const override ;
    Set& Substract(const Set& b) const override ;

    void Print(ostream& os) const override ;
};