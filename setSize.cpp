#pragma once

#include <iostream>
using namespace std;

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
    Cardinality(const int size) : Cardinality(size, false, false, 1) {}
    Cardinality() : Cardinality(-1, false, false, -1) {}
    Cardinality(int size, bool undefined, bool infinite, int sizepow)
    : elementCount(size), undefined(undefined), infinite(infinite), sizepower(sizepow)
    {
        if(undefined) {elementCount = -1;}
        if(elementCount < 0) {infinite = true; }
        if(infinite) {sizepower = maxint(sizepower, INFINITY_POW); elementCount = -1;}

        if(elementCount > 0) {sizepower = FINITE_POW;}
        else if(elementCount == 0) {sizepower = 0;}
    }

    friend ostream& operator <<(ostream& os, const Cardinality& me);

    bool operator < (const Cardinality& o) const {
        if(sizepower == o.sizepower) {
            return elementCount < o.elementCount;
        }
        else if (sizepower < o.sizepower) {return true;}
        else if (sizepower > o.sizepower) {return false;}
        
        return false;
    }
    bool operator > (const Cardinality& o) const {
        if(sizepower == o.sizepower) {
            return elementCount > o.elementCount;
        }
        else if (sizepower > o.sizepower) {return true;}
        else if (sizepower < o.sizepower) {return false;}
        
        return false;
    }
    bool operator == (const Cardinality& o) const {
        return (sizepower == o.sizepower) && (elementCount == o.elementCount) && (!(undefined || o.undefined));
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
        os << "I:" << me.sizepower;
    }
    else {throw "WTF???";}

    return os;
}

class ISizeable {
protected:
    ISizeable(Cardinality size) : Size(size) {}
    ISizeable(int size, bool undefined, bool infinite, int sizepow) : Size(size, undefined, infinite, sizepow) {} 
    ISizeable() : ISizeable(-1, true, false, -1) {}
public:
    const Cardinality Size;
};