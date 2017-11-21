#pragma once

#include "Element.h"
#include "util.cpp"

class Set : public virtual Element, public virtual IComparable<Set> {
protected:
    Set(const int size); //: Size(size) {}
    Set(); // : Size(-1) {} //infinite by default
public:
    const int Size;
    bool EmptyQ() const ;
    bool virtual Contains(const Element& e) const = 0;

    bool virtual Includes(const Set& s) const ;
    bool equal(const Set& a, const Set& b) const override;

    bool operator >=(const Set& o) const ;
    bool operator <=(const Set& o) const ;

    virtual Set& Sum(const Set& b) const = 0;
    virtual Set& Intersect(const Set& b) const = 0;
    virtual Set& Substract(const Set& b) const = 0;
};

class FunctionalSet : public virtual Set{
public:
    Set& Sum(const Set& b) const override ;
    Set& Intersect(const Set& b) const override ;
    Set& Substract(const Set& b) const override ;
};

class SubSet : public FunctionalSet{
protected:
    const RulePtr func;
    const Set &parent;
public:
    SubSet(const Set &p, const RulePtr f);// : parent(p), func(f) {}
    bool Contains(const Element& e) const override ;//{return parent.Contains(e) && func(e);}
};

class IForAll {
public: virtual bool ForAll(RulePtr& r) const = 0;
};
class IExists{
public: virtual bool Exists(RulePtr& r) const = 0;
};

class Uniwersum : public Set, public IForAll, public IExists{
public:
    bool Contains(const Element& e) const override {return true;}
    bool Includes(const Set& s) const override {return true;}
    
    bool ForAll(RulePtr& r) const override {return false;}
    bool Exists(RulePtr& r) const override {return true;}

    Set& Sum(const Set& b) const override {return (Set&)*this;}
    Set& Intersect(const Set& b) const override {return (Set&)b;}
    Set& Substract(const Set& b) const override {
        const RulePtr rule { [this, &b](const Element& e){ return !b.Contains(e); } };
        return *(new SubSet(*this, rule));
    }
};

const Uniwersum* const Uniwerse = new const Uniwersum{};