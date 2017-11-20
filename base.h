#pragma once

#include "Element.h"
#include "util.cpp"
#include "initializator.cpp"

class StaticElement : public Element{
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
        cout << "Created StaticElement: ";
        print();
        cout << endl;
    }
    void print() const {
        cout << '[' << ' ';
        for(int i = 0; i < size; i++){ cout << (int)obj[i] << ' ' ;}
        cout << ']';
    }

    virtual bool operator ==(const Element &other) const override {
        auto el = ToType<const StaticElement*>(&other);
        if(el) {return StaticElement::equal(*this, *el);}
        else{return false;}
    }
    virtual bool operator ==(const StaticElement& other) const { return equal(*this, other); }
    static bool equal(const StaticElement& a, const StaticElement& b) {
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

class Set : public virtual Element, public virtual IComparable<Set> {
    protected:
    Set(const int size); //: Size(size) {}
    Set(); // : Size(-1) {} //infinite by default
    public:
    const int Size;
    bool EmptyQ() const ;
    bool virtual Contains(const Element& e) const = 0;

    //[[todo]]
    bool virtual Includes(const Set& s) const ;
    bool equal(const Set& a, const Set& b) const override;

    bool operator ==(const Set& o) const ;
    bool operator >=(const Set& o) const ;
    bool operator <=(const Set& o) const ;
};

class FunctionalSet : public Set{
protected:
    const RulePtr func;
public:
    FunctionalSet(const RulePtr &f);
    bool Contains(const Element &e) const override ;
};

class SubSet : public FunctionalSet{
protected:
    const Set &parent;
public:
    SubSet(const Set &p, const RulePtr &f);// : parent(p), func(f) {}
    bool Contains(const Element& e) const override ;//{return parent.Contains(e) && func(e);}
};

class IForAll {
public: virtual bool ForAll(RulePtr& r) const = 0;
};
class IExists{
public: virtual bool Exists(RulePtr& r) const = 0;
};

class FiniteSet : public Set, public IForAll, public IExists {
protected:
    const Element** const list;
public:
    FiniteSet(const Element** es, int size);
    FiniteSet(Initial& v);

    bool Contains(const Element& e) const override;

    bool ForAll(RulePtr& r) const override ;
    bool Exists(RulePtr& r) const override ;
};
