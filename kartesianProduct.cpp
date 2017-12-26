#pragma once

#include "setSize.cpp"
#include "set.h"
#include "fset.h"
#include "kartesianProduct.h"

#include <iostream>
using namespace std;

FunctionalKartesianSet::FunctionalKartesianSet(const Set** list, const int size)
 : KartesianProduct(size), ISizeable(), ISetCollection(list) {}
bool FunctionalKartesianSet::Contains(const Element& e) const {
    // cout << "IM HERE!" << endl;
    
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
            els[z++] = new OrderedPair(*a.list[i], *b.list[k]);
        }
    }

    return *new FiniteSet(els, n);
}