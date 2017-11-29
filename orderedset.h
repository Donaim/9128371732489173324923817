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
    const Element& Get(int index) const override; 

    bool virtual Includes(const Set& s) const override;
};