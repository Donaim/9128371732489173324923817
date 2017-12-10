#pragma once

#include "set.h"
#include "fset.h"
#include "orderedset.h"
#include "util.cpp"

class Relation : public virtual SubSet {
public:
    const int ArgLength;
public:
    Relation(const Set& kProduct, int arguments) : SubSet(kProduct), ArgLength(arguments) {}

    virtual bool Contains(const Element& e) const override {
        const IOrderedSet* o = ToType<const IOrderedSet*>(&e);
        
        if(o) {
            if(o->Count() == ArgLength && Parent.Contains(e)) { return Defines(*o); }
        }
        
        return false;
    }

    virtual bool Defines(const IOrderedSet& o) const = 0;
};