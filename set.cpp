#pragma once

#include "set.h"
#include "fset.h"

using namespace std;

#define INCLUDE_ERRORS true

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
        throw "Set does not support ForAll quantifier :(";
    #endif
        return false;
    }
}
bool Set::equal (const Set& a, const Set& b) const {return a.Includes(b) && b.Includes(a);}
bool Set::operator >=(const Set& o) const{ return this->Includes(o); }
bool Set::operator <=(const Set& o) const{ return o.Includes((*this)); }

Set& FunctionalSet::Sum(const Set& b) const {
    const RulePtr rule { [this, &b](const Element& e){ return this->Contains(e) || b.Contains(e); } };
    return *(new RSubSet(*Uniwerse, rule));
}

Set& FunctionalSet::Intersect(const Set& b) const {
    const FiniteSet* bb = ToType<const FiniteSet*>(&b);
    if(bb) { return bb->Sum(*this); }
    else {
        const RulePtr rule { [&b](const Element& e){ return b.Contains(e); } };
        return *(new RSubSet(*this, rule));    
    }
}
Set& FunctionalSet::Substract(const Set& b) const {
    const RulePtr rule { [this, &b](const Element& e){ return !b.Contains(e); } };
    return *(new RSubSet(*this, rule));
}

RSubSet::RSubSet(const Set &p, const RulePtr f) : SubSet(p), func(f), ISizeable(-1) {}
bool RSubSet::Contains(const Element& e) const {return Parent.Contains(e) && func.F(e);}

SubSet::SubSet(const Set &p) : Parent(p) {}