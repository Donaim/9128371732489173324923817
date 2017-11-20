#pragma once

#include "util.cpp"
#include "set.h"
#include "initializator.cpp"

#include <iostream>
using namespace std;

#define INCLUDE_ERRORS true

Set::Set(const int size) : Size(size) {}
Set::Set() : Size(-1) {} //infinite by default
bool Set::EmptyQ() const {return Size == 0;}
bool Set::Includes(const Set& s) const {
    const IForAll* o = ToType<const IForAll*>(&s);
    if(o) 
    { 
        RulePtr rule { [this](const Element& e){ return this->Contains(e); } };
        return o->ForAll(rule);
    }
    else 
    {
    #if INCLUDE_ERRORS
            throw "Set does not support ForAll quantifikator :(";
    #endif
        return false;
    }
}
bool Set::equal (const Set& a, const Set& b) const {return a.Includes(b) && b.Includes(a);}
bool Set::operator ==(const Set& o) const{ return equal(*this, o); }
bool Set::operator >=(const Set& o) const{ return this->Includes(o); }
bool Set::operator <=(const Set& o) const{ return o.Includes((*this)); }

FunctionalSet::FunctionalSet(const RulePtr &r) : func(r) {}
bool FunctionalSet::Contains(const Element &e) const {return func.F(e);}

SubSet::SubSet(const Set &p, const RulePtr &f) : parent(p), FunctionalSet(f) {}
bool SubSet::Contains(const Element& e) const {return parent.Contains(e) && func.F(e);}

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

class Uniwersum : public Set, public IForAll, public IExists{
    bool Contains(const Element& e) const override {return true;}
    bool Includes(const Set& s) const override {return true;}
    
    bool ForAll(RulePtr& r) const override {return false;}
    bool Exists(RulePtr& r) const override {return true;}
};