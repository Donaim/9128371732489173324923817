#pragma once

#include "fset.h"
#include "orderedset.h"

FiniteSet::FiniteSet(const Element** es, int size) : Set(size), list(es) {}
FiniteSet::FiniteSet(Initial& v) : Set(v.size()), list(v.Get()) {}
bool FiniteSet::Contains(const Element& e) const {
    for(int i = 0; i < Size; i++) {
        if(*list[i] == e){return true;}
    }
    return false;
}
bool FiniteSet::ForAll(const RulePtr& r) const {
    for(int i = 0; i < Size; i++){
        if(!r.F(*list[i])) {return false;}
    }
    return true;
}
bool FiniteSet::Exists(const RulePtr& r) const {
    for(int i = 0; i < Size; i++){
        if(r.F(*list[i])) {return true;}       
    }  
    return false;
}
Set& FiniteSet::Sum(const Set& b) const {
    const FiniteSet* bb = ToType<const FiniteSet*>(&b);
    if(bb) {
        int n = bb->Size + this->Size;
        const Element** nlist = new const Element*[n];
        for(int i = 0; i < this->Size; i++) {nlist[i] = this->list[i];}
        for(int i = 0, k = this->Size; k < n; i++, k++) {nlist[k] = bb->list[i];}

        return *new FiniteSet(nlist, n);
    }
    else { return b.Sum(*this); }
}
Set& FiniteSet::Intersect(const Set& b) const {
    int n = (b.Size >= 0 && b.Size < this->Size) ? b.Size : this->Size;
    const Element** nlist = new const Element*[n];

    int count = 0;
    for(int i = 0; i < this->Size; i++){
        if(b.Contains(*this->list[i])) {nlist[count++] = this->list[i];}
    }

    return *new FiniteSet(nlist, count);
}
Set& FiniteSet::Substract(const Set& b) const {
    int n = this->Size;
    const Element** nlist = new const Element*[n];

    int count = 0;
    for(int i = 0; i < this->Size; i++){
        if(!b.Contains(*this->list[i])) {nlist[count++] = this->list[i];}
    }

    return *new FiniteSet(nlist, count);
}

const FiniteSet& FiniteSet::KartesianProduct(const FiniteSet& o) const {
    const int n = o.Size * this->Size;
    const Element **els = new const Element*[n];

    int z = 0;
    for(int i = 0, to = this->Size; i < to; i++)
    {
        for(int k = 0; k < o.Size; k++)
        {
            const Element **pair = new const Element*[2];
            pair[0] = this->list[i];
            pair[1] = o.list[k];
            els[z++] = new FiniteOrderedSet(pair, 2);
        }
    }

    return *new FiniteSet(els, n);
}

void FiniteSet::Print(ostream& os) const {
    if(Size <= 0) { os << '{' << '}'; return; }
    
    os << '{' << ' ';
    for(int i = 0; i < Size; i++) {
        IPrintable::printElement(os, list[i]);
        os << ' ';
    }
    os << '}';
}