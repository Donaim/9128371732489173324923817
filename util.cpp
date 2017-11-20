#pragma once

#include <functional>
#include <utility>
#include "Element.h"

//usage : IsTypeOf<TargetType>(&Element)
template<class T, class z>
bool IsTypeOf(const z ptr){
    if (dynamic_cast<const T*>(ptr)) {
        return true;
    }
    return false;
}

template<class T, class z>
T ToType(const z ptr)
{
    return dynamic_cast<const T>(ptr);
}

struct RulePtr
{
    //use: RulePtr rule { [this](const Element& e){ return this->Contains(e); } };
    using DecisionFn = std::function<bool(const Element&)>;
    RulePtr(DecisionFn dec) : F {std::move(dec)} {}
    DecisionFn F;
};


template <class T>
class IComparable : public virtual Element {
    virtual bool equal(const T& a, const T& b) const = 0;
    
    bool operator == (const Element& o) const override {
        const T* a = ToType<const T*>(this);
        const T* b = ToType<const T*>(&o);
        
        if(b) {return equal(*a, *b);}
        else {return false;}
    } 
};