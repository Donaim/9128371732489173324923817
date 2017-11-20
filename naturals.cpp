#pragma once

#include <iostream>
using namespace std;

#include "base.cpp"
#include "util.cpp"
#include "initializator.cpp"

class Natural : public virtual Element, public virtual IComparable<Natural> {
public:
    const unsigned int X;
    Natural(unsigned int x) : X(x) {}
    Natural(int x) : X(x < 0 ? 0 : x) {}

    // bool operator == (const Element& o) const override {
    //     auto el = ToType<const Natural*>(&o);
    //     if(el) {return Natural::equal(*this, *el);}
    //     else {return false;}
    // }
    // bool operator == (const Natural& o) {return equal(*this, o);}
    
    bool equal(const Natural& a, const Natural& b) const override {return a.X == b.X;} 
};

class Naturals : public Set {
public:
    Naturals() : Set() {}
    bool Contains(const Element& e) const override { return IsTypeOf<Natural>(&e); }

    //static FiniteSet Create()
};