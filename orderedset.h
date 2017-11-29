#pragma once

#include "Element.h"
#include "set.h"
#include "fset.h"

class IOrdered {
public:
    const virtual Element& Get(int index) const = 0; 
};

class FiniteOrderedSet : public virtual FiniteSet, public IOrdered {
protected:
public:
    FiniteOrderedSet() : FiniteSet(nullptr, 0) {}
    bool equal(const Set& a, const Set& b) const override;
    bool equal(const FiniteOrderedSet& a, const FiniteOrderedSet& b) const;
    const Element& Get(int index) const override; 
};