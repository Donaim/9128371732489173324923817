#pragma once

#include "set.h"
#include "fset.h"

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
        throw new SetEx("Set does not support ForAll quantifier :(");
    #endif
        return false;
    }
}
bool Set::equal (const Set& b) const {return this->Includes(b) && b.Includes(*this);}
bool Set::operator >=(const Set& o) const{ return this->Includes(o); }
bool Set::operator <=(const Set& o) const{ return o.Includes((*this)); }

Set& FunctionalSet::Union(const Set& b) const {
    const RulePtr rule { [this, &b](const Element& e){ return this->Contains(e) || b.Contains(e); } };
    return *(new RSubSet(*Uniwerse, rule));
}

Set& FunctionalSet::Intersect(const Set& b) const {
    const FiniteSet* bb = ToType<const FiniteSet*>(&b);
    if(bb) { return bb->Union(*this); }
    else {
        const RulePtr rule { [&b](const Element& e){ return b.Contains(e); } };
        return *(new RSubSet(*this, rule));    
    }
}
Set& FunctionalSet::Substract(const Set& b) const {
    const RulePtr rule { [this, &b](const Element& e){ return !b.Contains(e); } };
    return *(new RSubSet(*this, rule));
}

SubSet::SubSet(const Set &p) : Parent(p) {}
bool SubSet::Contains(const Element& e) const { return Parent.Contains(e) && Filter(e);}

RSubSet::RSubSet(const Set &p, const RulePtr f) : SubSet(p), func(f), ISizeable(-1) {}
bool RSubSet::Filter(const Element& e) const {return func.F(e);}
