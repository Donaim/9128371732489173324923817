#pragma once

#include <iostream>
using namespace std;

#include "set.cpp"
#include "util.cpp"
#include "initializator.cpp"

class Natural : public virtual Element, public virtual IComparable<Natural>, public IPrintable {
public:
    const unsigned int X;
    Natural(unsigned int x) : X(x) {}
    Natural(int x) : X(x < 0 ? 0 : x) {}
    
    bool equal(const Natural& a, const Natural& b) const override {return a.X == b.X;} 

    void Print(ostream& os) const override { os << X; }
};

class Naturals : public FunctionalSet {
public:
    bool Contains(const Element& e) const override { return IsTypeOf<Natural>(&e); }
};