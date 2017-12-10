#pragma once

#include "setSize.cpp"
#include "set.h"
#include "fset.h"
#include "kartesianProduct.h"

#include <iostream>
using namespace std;

FunctionalKartesianSet::FunctionalKartesianSet(const Set** list, const int size) : list(list), KartesianProduct(size), ISizeable() {}
bool FunctionalKartesianSet::Contains(const Element& e) const {
    const IOrderedSet* o = ToType<const IOrderedSet*>(&e);

    if(o)
    {
        if(o->Size != this->PairSize) {return false;}
        for(int i = 0, to = o->Size.Count(); i < to; i++){
            if(!this->list[i]->Contains(o->Get(i))) {return false;}
        }

        return true;
    }
    else { return false; }
}

const FiniteSet& FiniteKartesianPSet::product(const FiniteSet& a, const FiniteSet& b) {
    const int osize = b.Size.Count(), tsize = a.Size.Count();
    const int n = osize * tsize;
    const Element **els = new const Element*[n];
    
    int z = 0;
    for(int i = 0, to = tsize; i < to; i++)
    {
        for(int k = 0; k < osize; k++)
        {
            const Element **pair = new const Element*[2];
            pair[0] = a.list[i];
            pair[1] = b.list[k];
            els[z++] = new FiniteOrderedSet(pair, 2);
        }
    }

    return *new FiniteSet(els, n);
}