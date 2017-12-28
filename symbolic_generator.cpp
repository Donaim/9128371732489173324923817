#pragma once

#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

#include "set.cpp"
#include "util.cpp"
#include "generator.cpp"

class Symbol : public virtual Element, public virtual IComparable<Symbol>, public IPrintable {
    static int intlog(double base, double x) {
        return (int)(log(x) / log(base));
    }
    static const int char_range = 'z' - 'a' + 1;
    static const char get(int x) { return x + 'a'; }
    static const char * toStr(int n) 
    {
        int len = intlog(char_range, n + 1) + 1;
        char tmp[len];

        int i = 0;
        do
        {
            int x = (n - 1) % char_range;
            tmp[i++] = get(x);
            n = (n - x) / char_range;
        }
        while(n > 0);

        char * re = new char[i + 1]; 
        for(int k = 0, j = i - 1; k < i; k++, j--) { re[j] = tmp[k]; }
        re[i] = '\0';

        return re;
    }
public:
    const char * const str;
    Symbol(unsigned int x) : Symbol((int)x) { }
    Symbol(int x) : str(toStr(x < 1 ? 1 : x)) { }
    Symbol(char c) : str(new char[1] {c}) {}
    Symbol(const char * s) : str(s) {}

    bool equal(const Symbol& b) const override { return strcmp(this->str, b.str) == 0; } 

    void Print(ostream& os) const override { os << str; }

    static const char * C(const Element& e) { return conv<Symbol>(e).str; }
};

class Symbolics : public FunctionalSet, public IGeneratable {
public:
    Symbolics() : ISizeable(-1, false, true, 2) {}
    bool Contains(const Element& e) const override { return IsTypeOf<Symbol>(&e); }
protected:
    Element& GenElement(int x, int mode) const override { return *new Symbol{x}; }
};