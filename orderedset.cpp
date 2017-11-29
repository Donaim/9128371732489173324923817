#pragma once

#include "orderedset.h"

bool FiniteOrderedSet::equal(const Set& a, const Set& b) const {
    const FiniteOrderedSet* fos = ToType<const FiniteOrderedSet*>(&b);
    if(fos) 
    {
        return equal(*this, *fos);
    }
    else {return false;}
}
bool FiniteOrderedSet::equal(const FiniteOrderedSet& a, const FiniteOrderedSet& b) const {
    if(a.Size != b.Size){return false;}
    for(int i = 0; i < a.Size; i++) {
        if(!(*a.list[i] == *b.list[i])) {return false;}
    }
    return true;
}

const Element& FiniteOrderedSet::Get(int index) const { return *FiniteSet::list[index]; } 