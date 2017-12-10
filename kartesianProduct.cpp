#pragma once

#include "setSize.cpp"
#include "set.h"
#include "fset.h"
#include "kartesianProduct.h"

FunctionalKartesianSet::FunctionalKartesianSet(const Set** list, const int size) : list(list), KartesianProduct(size), ISizeable() {}
bool FunctionalKartesianSet::Contains(const Element& e) const {
    const IOrderedSet* o = ToType<const IOrderedSet*>(&e);

    if(o)
    {
        if(o->Count() != this->PairSize.Count()) {return false;}
        for(int i = 0, to = o->Count(); i < to; i++){
            if(!this->list[i]->Contains(o->Get(i))) {return false;}
        }

        return true;
    }
    else { return false; }
} 