#pragma once

#include <iostream>
using namespace std;

#include "set.cpp"
#include "util.cpp"
#include "generator.cpp"

class Natural : public virtual Element, public virtual IComparable<Natural>, public IPrintable {
public:
    const unsigned int X;
    Natural(unsigned int x) : X(x) {}
    Natural(int x) : X(x < 0 ? 0 : x) {}
    
    bool equal(const Natural& b) const override {return this->X == b.X;} 

    void Print(ostream& os) const override { os << X; }

    static int C(const Element& e) { return conv<Natural>(e).X; }
};

class Naturals : public FunctionalSet, public IGeneratable {
public:
    Naturals() : ISizeable(-1, false, true, 2) {}
    bool Contains(const Element& e) const override { return IsTypeOf<Natural>(&e); }
protected:
    Element& GenElement(int x, int mode) const override { return *new Natural{x}; }
};