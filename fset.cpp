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
    if(bb){
        // auto c = bb->Includes(*this);

        auto n = bb->Size + this->Size;
        Element** nlist = new Element*[n];
        for(int i = 0; i < this->Size; i++) {nlist[i] = (Element*)this->list[i];}
        for(int i = 0, k = this->Size; k < n; i++, k++) {nlist[k] = (Element*)bb->list[i];}

        return *new FiniteSet((const Element**)nlist, n);
        // return ((FiniteSet&)(*bb));
    }
    else {
        const FunctionalSet* cc = ToType<const FunctionalSet*>(&b);
        if(cc){ return cc->Sum(*this); }
        else{ throw 0; }
    }
}
Set& FiniteSet::Intersect(const Set& b) const {
    throw 0;
}
Set& FiniteSet::Substract(const Set& b) const {
    throw 0;
}


void FiniteSet::Print(ostream& os) const {
    os << '{' << ' ';
    for(int i = 0; i < Size; i++) {
        auto ip = ToType<const IPrintable*>(list[i]);
        auto set = ToType<const Set*>(list[i]);
        
        if(ip) {cout << *ip;}
        else if(set) {cout << "{?}";} //Not printable set
        // else { IPrintable::Default(list[i]); }
        else {cout << '?';}
        
        cout << ' ';
    }
    os << '}';
}