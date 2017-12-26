#pragma once

#include <iostream>

#include "exceptions.cpp"

using namespace std;

#define UNDEFINED_SIZE_ERROR false

class Cardinality {
    const bool undefined;
    int elementCount;
    bool infinite;
    int sizepower;

    static inline int maxint(const int a, const int b) { return a > b ? a : b; }
#define INFINITY_POW 2
#define FINITE_POW 1
public:
    bool UndefinedQ() const {return undefined;}
    int Count() const {return elementCount;}
    bool InfiniteQ() const {return infinite;}
    int Power() const {return sizepower;}
    bool EmptyQ() const {return elementCount == 0;}

public:
    explicit Cardinality(const int size) : Cardinality(size, false, false, 1) {}
    explicit Cardinality() : Cardinality(-1, false, false, -1) {}
    explicit Cardinality(int size, bool undefined, bool infinite, int sizepow)
    : elementCount(size), undefined(undefined), infinite(infinite), sizepower(sizepow)
    {
        if(undefined) {elementCount = -1;}
        if(elementCount < 0) {infinite = true; }
        if(infinite) {sizepower = maxint(sizepower, INFINITY_POW); elementCount = -1;}

        if(elementCount > 0) {sizepower = FINITE_POW;}
        else if(elementCount == 0) {sizepower = 0;}

#if UNDEFINED_SIZE_ERROR
        if(undefined) { throw new SetEx("Set with undefined size created!"); }
#endif
    }

    friend ostream& operator <<(ostream& os, const Cardinality& me);

    bool operator < (const Cardinality& o) const {
        if(this->undefined || o.undefined) { throw new SetEx("Attempt to compare size of set with undefined size!"); }

        if(sizepower == o.sizepower) {
            return elementCount < o.elementCount;
        }
        else if (sizepower < o.sizepower) {return true;}
        else if (sizepower > o.sizepower) {return false;}
        
        return false;
    }
    bool operator > (const Cardinality& o) const {
        if(this->undefined || o.undefined) { throw new SetEx("Attempt to compare size of set with undefined size!"); }
      
        if(sizepower == o.sizepower) {
            return elementCount > o.elementCount;
        }
        else if (sizepower > o.sizepower) {return true;}
        else if (sizepower < o.sizepower) {return false;}
        
        return false;
    }
    bool operator == (const Cardinality& o) const {
        if(this->undefined || o.undefined) { throw new SetEx("Attempt to compare size of set with undefined size!"); }

        return (sizepower == o.sizepower) && (elementCount == o.elementCount);
    }
    bool operator != (const Cardinality& o) const { return !( *this == o ); }
};
ostream& operator << (ostream& os, const Cardinality& me) {
    if(me.elementCount >= 0){
        os << me.elementCount;
    }
    else if(me.undefined){
        os << "NA";
    }
    else if(me.infinite){
        os << "∞";
        if(me.sizepower > INFINITY_POW) {os << ":" << me.sizepower; }
    }
    else {throw new SetEx("WTF???");}

    return os;
}

class ISizeable {
protected:
    explicit ISizeable(Cardinality size) : Size(size) {}
    explicit ISizeable(int size, bool undefined, bool infinite, int sizepow) : Size(size, undefined, infinite, sizepow) {} 
    explicit ISizeable() : ISizeable(-1, true, false, -1) {}
    explicit ISizeable(int size) : ISizeable(size, false, false, 1) {}
public:
    const Cardinality Size;
};