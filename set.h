#pragma once

#include "Element.h"
#include "util.cpp"
#include "initializator.cpp"

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

    //bool operator ==(const Set& o) const ;
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
