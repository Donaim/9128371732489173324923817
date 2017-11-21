#pragma once

#include "set.h"
#include "fset.h"

using namespace std;

#define INCLUDE_ERRORS true

Set::Set(const int size) : Size(size) {}
Set::Set() : Size(-1) {} //infinite by default
bool Set::EmptyQ() const {return Size == 0;}
bool Set::Includes(const Set& s) const {
    const IForAll* o = ToType<const IForAll*>(&s);
    if(o) 
    { 
        const RulePtr rule { [this](const Element& e){ return this->Contains(e); } };
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
bool Set::operator >=(const Set& o) const{ return this->Includes(o); }
bool Set::operator <=(const Set& o) const{ return o.Includes((*this)); }

Set& FunctionalSet::Sum(const Set& b) const {
    const RulePtr rule { [this, &b](const Element& e){ return this->Contains(e) || b.Contains(e); } };
    return *(new SubSet(*Uniwerse, rule));
}

Set& FunctionalSet::Intersect(const Set& b) const {
    const FiniteSet* bb = ToType<const FiniteSet*>(&b);
    if(bb) { return bb->Sum(*this); }
    else {
        const RulePtr rule { [&b](const Element& e){ return b.Contains(e); } };
        return *(new SubSet(*this, rule));    
    }
}
Set& FunctionalSet::Substract(const Set& b) const {
    const RulePtr rule { [this, &b](const Element& e){ return !b.Contains(e); } };
    return *(new SubSet(*this, rule));
}

SubSet::SubSet(const Set &p, const RulePtr f) : parent(p), func(f) {}
bool SubSet::Contains(const Element& e) const {return parent.Contains(e) && func.F(e);}

