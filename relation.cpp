#pragma once

#include "relation.h"

Relation::Relation(const KartesianProduct &kProduct) : SubSet(kProduct), kProduct(kProduct) {}
bool Relation::Filter(const Element& e) const {
    const IOrderedSet* o = ToType<const IOrderedSet*>(&e);
    if(o) {
        if(o->Size == kProduct.PairSize) { return Defines(*o); }
    }
    
    return false;
}

