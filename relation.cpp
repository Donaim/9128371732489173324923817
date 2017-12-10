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

    virtual bool Contains(const Element& e) const override {
        const IOrderedSet* o = ToType<const IOrderedSet*>(&e);
        
        if(o) {
            if(o->Size == kProduct.PairSize && Parent.Contains(e)) { return Defines(*o); }
        }
        
        return false;
    }

    virtual bool Defines(const IOrderedSet& o) const = 0;
};