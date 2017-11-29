#pragma once

#include "orderedset.h"

bool FiniteOrderedSet::Includes(const Set& s) const {
    if(s.Size > this->Size) {return false;}
    
    const IOrdered* o = ToType<const IOrdered*>(&s);
    if(o)
    {
        for(int i = 0, to = s.Size; i < to; i++){
            if(!(o->Get(i) == *(this->list[i]))) {return false;}
        }

        return true;
    }
    else { return false; }
}

const Element& FiniteOrderedSet::Get(int index) const { return *FiniteSet::list[index]; } 