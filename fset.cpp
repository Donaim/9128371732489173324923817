#pragma once

#include "fset.h"

FiniteSet::FiniteSet(const Element** es, int size) : ISizeable(size), list(es) {}
FiniteSet::FiniteSet(Initial& v) : ISizeable(v.size()), list(v.Get()) {}
bool FiniteSet::Contains(const Element& e) const {
    for(int i = 0, to = Size.Count(); i < to; i++) {
        if(*list[i] == e){return true;}
    }
    return false;
}
bool FiniteSet::ForAll(const RulePtr& r) const {
    for(int i = 0, to = Size.Count(); i < to; i++){
        if(!r.F(*list[i])) {return false;}
    }
    return true;
}
bool FiniteSet::Exists(const RulePtr& r) const {
    for(int i = 0, to = Size.Count(); i < to; i++){
        if(r.F(*list[i])) {return true;}       
    }  
    return false;
}
Set& FiniteSet::Union(const Set& b) const {
    const FiniteSet* bb = ToType<const FiniteSet*>(&b);
    if(bb) {
        int bbsize = bb->Size.Count();
        int tsize = this->Size.Count();

        int n = bbsize + tsize;
        const Element** nlist = new const Element*[n];
        for(int i = 0; i < tsize; i++) {nlist[i] = this->list[i];}
        for(int i = 0, k = tsize; k < n; i++, k++) {nlist[k] = bb->list[i];}

        return *new FiniteSet(nlist, n);
    }
    else { return b.Union(*this); }
}
Set& FiniteSet::Intersect(const Set& b) const {
    // int n = (b.Size < this->Size) ? b.Size.Count() : this->Size.Count();
    int n = (b.Size.UndefinedQ() || b.Size > this->Size) ? this->Size.Count() : b.Size.Count(); 
    const Element** nlist = new const Element*[n];

    int count = 0;
    for(int i = 0, to = this->Size.Count(); i < to; i++){
        if(b.Contains(*this->list[i])) {nlist[count++] = this->list[i];}
    }

    return *new FiniteSet(nlist, count);
}
Set& FiniteSet::Substract(const Set& b) const {
    int n = this->Size.Count();
    const Element** nlist = new const Element*[n];

    int count = 0;
    for(int i = 0; i < n; i++){
        if(!b.Contains(*this->list[i])) {nlist[count++] = this->list[i];}
    }

    return *new FiniteSet(nlist, count);
}

void FiniteSet::Print(ostream& os) const {
    if(Size.UndefinedQ()) { os << "{f->?}"; return; }
    else if(Size.InfiniteQ()) { os << "{∞}"; return; }
    else if(Size.EmptyQ()) { os << '{' << '}'; return; }
    
    // cout << '!' << Count() << endl;

    os << '{' << ' ';
    for(int i = 0, to = Size.Count(); i < to; i++) {
        IPrintable::printElement(os, list[i]);
        os << ' ';
    }
    os << '}';
}