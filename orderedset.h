#pragma once

#include "Element.h"
#include "set.h"
#include "fset.h"

class IOrderedSet : public virtual Set {
public:
    const virtual Element& Get(int index) const = 0; 
};

class FiniteOrderedSet : public virtual IOrderedSet, public virtual FiniteSet {
public:
    FiniteOrderedSet(const Element **els, int size) : FiniteSet(els, size), ISizeable(size) {}
    const Element& Get(int index) const override; 

    bool virtual Includes(const Set& s) const override;
    
    void Print(ostream& os) const override ;
};
