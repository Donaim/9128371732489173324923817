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

class OrderedPairsFunctionalSet : public virtual FunctionalSet {
protected:
    const int pairLen;
    const Set** list;
public:
    OrderedPairsFunctionalSet(const Set** list, const int size); // : list(list), pairLen(size) {}
    bool Contains(const Element& e) const override ;
};