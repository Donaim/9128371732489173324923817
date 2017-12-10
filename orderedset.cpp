#pragma once

#include "fset.h"
#include "orderedset.h"

bool FiniteOrderedSet::Includes(const Set& s) const {
    const IOrderedSet* o = ToType<const IOrderedSet*>(&s);
    if(o)
    {
        if(o->Count() > this->Count()) {return false;}
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
    const IOrderedSet* o = ToType<const IOrderedSet*>(&e);

    if(o)
    {
        if(o->Count() != this->pairLen) {return false;}
        for(int i = 0, to = o->Count(); i < to; i++){
            if(!this->list[i]->Contains(o->Get(i))) {return false;}
        }

        return true;
    }
    else { return false; }
} 