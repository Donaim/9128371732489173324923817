#pragma once

#include <iostream>

class SetSize {
    const bool undefined;
    int elementCount;
    bool infinite;
    int sizepower;

    static inline int maxint(const int a, const int b) { return a > b ? a : b; }
#define INFINITY_POW 2
#define FINITE_POW 1

public:
    SetSize(int size, bool undefined, bool infinite, int sizepow) 
    : elementCount(size), undefined(undefined), infinite(infinite), sizepower(sizepow)
    {
        if(undefined) {elementCount = -1;}
        if(elementCount < 0) {infinite = true; }
        if(infinite) {sizepower = maxint(sizepower, INFINITY_POW); elementCount = -1;}

        if(elementCount > 0) {sizepower = FINITE_POW;}
        else if(elementCount == 0) {sizepower = 0;}
    }

    friend ostream& operator <<(ostream& os, const SetSize& me);

    SetSize& operator + (const SetSize& o) const {
        return *new SetSize(
            elementCount + o.elementCount,
            undefined || o.undefined, 
            infinite || o.infinite,
            maxint(sizepower, o.sizepower)
            );
    }
    SetSize& operator * (const SetSize& o) const {
        return *new SetSize(
            elementCount * o.elementCount,
            undefined || o.undefined, 
            infinite || o.infinite,
            maxint(sizepower, o.sizepower)
            );
    }
    bool operator < (const SetSize& o) const {
        if(sizepower == o.sizepower) {
            return elementCount < o.elementCount;
        }
        else if (sizepower < o.sizepower) {return true;}
        else if (sizepower > o.sizepower) {return false;}
        
        return false;
    }
    bool operator > (const SetSize& o) const {
        if(sizepower == o.sizepower) {
            return elementCount > o.elementCount;
        }
        else if (sizepower > o.sizepower) {return true;}
        else if (sizepower < o.sizepower) {return false;}
        
        return false;
    }
};

ostream& operator << (ostream& os, const SetSize& me) {
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
public:
    ISizeable(const SetSize& size) : Size(size) {}
    const SetSize Size;
};