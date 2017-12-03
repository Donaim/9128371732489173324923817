#pragma once

#include "orderedset.h"

bool FiniteOrderedSet::Includes(const Set& s) const {
    if(s.Count() > this->Count()) {return false;}
    
    const IOrdered* o = ToType<const IOrdered*>(&s);
    if(o)
    {
        for(int i = 0, to = s.Count(); i < to; i++){
            if(!(o->Get(i) == *(this->list[i]))) {return false;}
        }

        return true;
    }
    else { return false; }
}

const Element& FiniteOrderedSet::Get(int index) const { return *FiniteSet::list[index]; } 

void FiniteOrderedSet::Print(ostream& os) const {
    if(UndefinedQ()) { os << "(f->?)"; return; }
    else if(InfiniteQ()) { os << "(∞)"; return; }
    else if(EmptyQ()) { os << '(' << ')'; return; }

    os << '(';
    IPrintable::printElement(os, list[0]);
    for(int i = 1, to = Count(); i < to; i++) {
        os << ',';
        IPrintable::printElement(os, list[i]);
    }
    os << ')';
}


OrderedPairsFunctionalSet::OrderedPairsFunctionalSet(const Set** list, const int size) : list(list), pairLen(size), ISizeable(size) {}
bool OrderedPairsFunctionalSet::Contains(const Element& e) const {
    throw 0;
    // const IOrdered* o = ToType<const IOrdered*>(&e);


    // if(o)
    // {
    //     for(int i = 0, to = s.Size; i < to; i++){
    //         if(!(o->Get(i) == *(this->list[i]))) {return false;}
    //     }

    //     return true;
    // }
    // else { return false; }
} 