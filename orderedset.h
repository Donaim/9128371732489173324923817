#pragma once

#include "Element.h"
#include "set.h"
#include "fset.h"

class IOrderedSet : public virtual Set, public virtual IPrintable {
public:
    const virtual Element& Get(int index) const = 0;
    bool Contains(const Element & e, int at) const ;

    bool virtual Includes(const Set& s) const override;

    virtual void Print(ostream& os) const override ;
};

class FiniteOrderedSet : public virtual IOrderedSet, public virtual FiniteSet {
public:
    FiniteOrderedSet(const Element **els, int size) : FiniteSet(els, size), ISizeable(size) {}
    const Element& Get(int index) const override; 

    void Print(ostream& os) const override ;
};

class OrderedPair : public virtual FiniteOrderedSet {
    static const Element** createPair(const Element &a, const Element &b) ;
    OrderedPair(const Element **els);
public:
    const Element& A() const ;
    const Element& B() const ;

    OrderedPair(const Element &a, const Element &b) ;
};


class TmpPair : public virtual FunctionalSet, public virtual IOrderedSet {
public:
    TmpPair() ;

    mutable const Element* x;
    mutable const Element* y;

    const Element& Get(int index) const override ;
    virtual bool Contains(const Element& e) const override ;

    virtual bool equal(const Set &b) const override ;
    bool equal(const Element &b) const ;
    virtual bool operator == (const Element &e) const override ;
};


class PairProduct : public virtual IOrderedSet {
public:
    const IOrderedSet & A, & B;
    PairProduct(const IOrderedSet & a, const IOrderedSet & b);

    virtual bool Contains(const Element & e) const override ; // check if of type of pair
    virtual bool Contains(const OrderedPair & p) const = 0;

    virtual const Element & Get(int index) const override ;
};



class FinitePairProduct : public virtual PairProduct, public virtual FiniteOrderedSet {
    static const Element** getList(const FiniteOrderedSet & a, const FiniteOrderedSet & b) ;
    FinitePairProduct(const FiniteOrderedSet & a, const FiniteOrderedSet & b, const Element** list) ;
public:
    FinitePairProduct(const FiniteOrderedSet & a, const FiniteOrderedSet & b) ;

    virtual bool Contains(const Element & e) const override ;
    virtual bool Contains(const OrderedPair & p) const override ;
    virtual const Element & Get(int) const override ;
};