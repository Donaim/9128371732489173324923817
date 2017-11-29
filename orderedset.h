#pragma once

#include "Element.h"
#include "set.h"
// #include "fset.h"

class FiniteSet;

class IOrdered {
public:
    const virtual Element& Get(int index) const = 0; 
};

class FiniteOrderedSet : public virtual FiniteSet, public IOrdered {
    FiniteOrderedSet() : FiniteSet(nullptr, 0) {}
protected:
public:
    FiniteOrderedSet(const Element **els, int size) : FiniteSet(els, size) {}
    const Element& Get(int index) const override; 

    bool virtual Includes(const Set& s) const override;
    
    void Print(ostream& os) const override ;
};