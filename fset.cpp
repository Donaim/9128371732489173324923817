#pragma once

#include "fset.h"

FiniteSet::FiniteSet(const Element** es, int size) : Set(size), list(es) {}
FiniteSet::FiniteSet(Initial& v) : Set(v.size()), list(v.Get()) {}
bool FiniteSet::Contains(const Element& e) const {
    for(int i = 0; i < Size; i++) {
        if(*list[i] == e){return true;}
    }
    return false;
}
bool FiniteSet::ForAll(RulePtr& r) const {
    for(int i = 0; i < Size; i++){
        if(!r.F(*list[i])) {return false;}
    }
    return true;
}
bool FiniteSet::Exists(RulePtr& r) const {
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

bool PRINT_FIRST_LAYER = false;

void FiniteSet::Print(ostream& os) const {
    if(Size <= 0) { os << '{' << '}'; return; }
    
    os << '{' << ' ';
    for(int i = 0; i < Size; i++) {
        auto ip = ToType<const IPrintable*>(list[i]);
        auto set = ToType<const Set*>(list[i]);
        
        if(PRINT_FIRST_LAYER){
            if(set) {cout << "{...}"; }
            else if(ip) {cout << *ip; }
            else {cout << '?'; }
        }
        else{
            if(ip) {cout << *ip;}
            else if(set) {cout << "{?}";} //Not printable set
            else {cout << '?';}
        }
        
        cout << ' ';
    }
    os << '}';
}