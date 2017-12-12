#pragma once

#include "set.h"
#include "fset.h"
#include "orderedset.h"
#include "kartesianProduct.h"
#include "util.cpp"

class Relation : public virtual SubSet {
public:
    const KartesianProduct &kProduct;
public:
    Relation(const KartesianProduct &kProduct) : SubSet(kProduct), kProduct(kProduct) {}

    virtual bool Filter(const Element& e) const override {
        const IOrderedSet* o = ToType<const IOrderedSet*>(&e);
        
        if(o) {
            if(o->Size == kProduct.PairSize) { return Defines(*o); }
        }
        
        return false;
    }

    virtual bool Defines(const IOrderedSet& o) const = 0;
};

class TmpPair : public virtual FunctionalSet, public virtual IOrderedSet {
public:
    TmpPair() : x(nullptr), y(nullptr), ISizeable(2) {}

    mutable const Element* x;
    mutable const Element* y;

    const Element& Get(int index) const override {
        switch(index){
            case 0: return *x;
            case 1: return *y;
            default: throw "Index out of range 2 !";
        }
    }

    virtual bool Contains(const Element& e) const override { return *x == e || *y == e; }
};

class PairRelation : public virtual Relation {
    static const ISetCollection& GetCollection(const KartesianProduct &kp) {
        const ISetCollection* re = ToType<const ISetCollection*>(&kp);
        if(re) 
        {
            if(kp.PairSize != *new Cardinality(2, false, false, 1)) { throw "Wrong PairSize! Expected=2 \n"; }
            return *re;
        }
        throw "Kartesian product is not of ISetCollection!";
    }

    PairRelation(const KartesianProduct &kProduct, const ISetCollection &scoll) 
        : Relation(kProduct), SubSet(kProduct),
        X(*scoll.list[0]), Y(*scoll.list[1]), 
        X_FA(ToType<const IForAll*> (scoll.list[0])), Y_FA(ToType<const IForAll*> (scoll.list[1])), 
        X_IE(ToType<const IExists*> (scoll.list[0])), Y_IE(ToType<const IExists*> (scoll.list[1])) 
        { }

    const IForAll * const X_FA, * const Y_FA;
    const IExists * const X_IE, * const Y_IE;
public:
    const Set &X, &Y;

    PairRelation(const KartesianProduct &kProduct) : PairRelation(kProduct, GetCollection(kProduct)) {}

    const Set& Domain() // dziedzina
    {
        if(!Y_IE) { throw "Y does not support IExists -> Cannot compute the domain"; }

        TmpPair* pair = new TmpPair{};

        RulePtr rule { [this, pair](const Element &e) 
        {
            pair->x = &e;

            RulePtr rule2 { [this, pair](const Element& e2)
            {
                // cout << "HELLO " <<endl;
                pair->y = &e2;
                return this->Contains(*pair);
            }};

            return Y_IE->Exists(rule2);
        }};

        return *new RSubSet(X, rule);
    }
    // const Set& CoDomain() 
};