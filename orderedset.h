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

class OrderedPair : public virtual FiniteOrderedSet {
    static const Element** createPair(const Element &a, const Element &b){
        const Element ** re = new const Element*[2];
        re[0] = &a;
        re[1] = &b;
        return re;
    }
    OrderedPair(const Element **els) : FiniteOrderedSet(els, 2), FiniteSet(els, 2), ISizeable(2) {}
public:
    const Element& A() const { return *FiniteSet::list[0]; }
    const Element& B() const { return *FiniteSet::list[1]; }
   
    OrderedPair(const Element &a, const Element &b) : OrderedPair(createPair(a, b)) {}
};
