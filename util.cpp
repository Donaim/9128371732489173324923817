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


class IPrintable {
public:
    friend ostream& operator<<(ostream& os, const IPrintable& o);
    virtual void Print(ostream& os) const = 0;

    template <class T>
    static void Default(T x) { cout << typeid(x).name(); }
};
ostream& operator << (ostream& os, const IPrintable& o){
    o.Print(os);
    return os;
}

template <class T>
class IComparable : public virtual Element {
public:
    virtual bool equal(const T& a, const T& b) const = 0;
    
    bool operator == (const Element& o) const override {
        const T* b = ToType<const T*>(&o);
        if(b) 
        {
            const T* a = ToType<const T*>(this);
            return equal(*a, *b);
        }
        else {return false;}
    } 
    bool operator == (const T& o) const {
        const T* a = ToType<const T*>(this);
        return equal(*a, o);
    }
};


class StaticElement : public virtual Element, public virtual IComparable<StaticElement>, public IPrintable {
    const uint8_t* const obj;
    const int size;
    const size_t id;
    
    template <typename T>
    static uint8_t* cpy(T& p){
        uint8_t* start = (uint8_t*)&p;
        uint8_t* copy = new uint8_t[sizeof(p)];
        for(int i = 0; i < sizeof(p); i++) {copy[i] = start[i];}

        return copy;
    }
    protected:
    public:
    template <typename T> 
    explicit StaticElement(T x) : obj(cpy(x)), size(sizeof(x)), id(type_index(typeid(x)).hash_code()) 
    {
    #if REPORT_CREATED 
        reportCreated();
    #endif
    }

    void reportCreated() const {
        cout << "Created StaticElement: " << *this << ';' << endl;
    }
    void Print(ostream& os) const override {
        os << '[' << ' ';
        for(int i = 0; i < size; i++){ os << (int)obj[i] << ' ' ;}
        os << ']';
    }

    bool equal(const StaticElement& a, const StaticElement& b) const override {
        if(
            a.size <= 0 || b.size <= 0
            || a.size != b.size
            || a.id != b.id
        ) {return false;}

        for(int i = 0; i < a.size; i++){
            if(a.obj[i] != b.obj[i]) {return false;}
        }
    }
};