#pragma once

#include <functional>
#include <utility>
#include "Element.h"
#include "exceptions.cpp"

class Set;

#define QUOTE(x) #x

//usage : IsTypeOf<TargetType>(&Element)
template<class T, class z>
bool IsTypeOf(const z ptr){
    if (dynamic_cast<const T*>(ptr)) {
        return true;
    }
    return false;
}

template<class T, class Z>
T ToType(const Z ptr)
{
    return dynamic_cast<const T>(ptr);
}
template<class T, class Z>
const T& conv(const Z& ptr)
{
    return *dynamic_cast<const T*>(&ptr);
}

struct RulePtr
{
    //use: RulePtr rule { [this](const Element& e){ return this->Contains(e); } };
    using DecisionFn = std::function<bool(const Element&)>;
    RulePtr(DecisionFn dec) : F {std::move(dec)} {}
    DecisionFn F;
};


#define PRINT_FIRST_LAYER false

class IPrintable {
public:
    friend ostream& operator<<(ostream& os, const IPrintable& o);
    virtual void Print(ostream& os) const = 0;

    template <class T>
    static void Default(T x) { cout << typeid(x).name(); }

    static void printElement(ostream& os, const Element* e){
        auto ip = ToType<const IPrintable*>(e);
        auto set = ToType<const Set*>(e);

#if PRINT_FIRST_LAYER
        if(set) {os << "{...}"; }
        else if(ip) {os << *ip; }
        else {os << '?'; }
#else
        if(ip) {os << *ip;}
        else if(set) {os << "{?}";} //Not printable set
        else {os << '?';}
#endif
    }
};
ostream& operator << (ostream& os, const IPrintable& o){
    o.Print(os);
    return os;
}

template <class T>
class IComparable : public virtual Element {
public:
    virtual bool equal(const T& b) const = 0;
    
    virtual bool operator == (const Element& o) const override {
        const T* b = ToType<const T*>(&o);
        if(b) 
        {
            return equal(*b);
        }
        else {return false;}
    }
    virtual bool operator == (const T& o) const { return equal(o); }
};