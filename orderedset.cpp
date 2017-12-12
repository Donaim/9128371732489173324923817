#pragma once

#include "fset.h"
#include "orderedset.h"

bool FiniteOrderedSet::Includes(const Set& s) const {
    const IOrderedSet* o = ToType<const IOrderedSet*>(&s);
    if(o)
    {
        // cout << o->Size << "vs" << this->Size << endl;
        if(o->Size > this->Size) {return false;}

        for(int i = 0, to = s.Size.Count(); i < to; i++){
            if(!(o->Get(i) == *(this->list[i]))) {return false;}
        }

        return true;
    }
    else { return false; }
}

const Element& FiniteOrderedSet::Get(int index) const 
{
    if(index > Size.Count()) { throw "index is out of range!"; } 
    return *FiniteSet::list[index]; 
} 

void FiniteOrderedSet::Print(ostream& os) const {
    if(Size.UndefinedQ()) { os << "(f->?)"; return; }
    else if(Size.InfiniteQ()) { os << "(∞)"; return; }
    else if(Size.EmptyQ()) { os << '(' << ')'; return; }

    os << '(';
    IPrintable::printElement(os, list[0]);
    for(int i = 1, to = Size.Count(); i < to; i++) {
        os << ',';
        IPrintable::printElement(os, list[i]);
    }
    os << ')';
}