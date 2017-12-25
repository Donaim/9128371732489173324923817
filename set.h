#pragma once

#include "Element.h"
#include "setSize.cpp"
#include "util.cpp"

class Set : public virtual Element, public virtual ISizeable, public virtual IComparable<Set> {
protected:
public:
    bool virtual Contains(const Element& e) const = 0;

    bool virtual Includes(const Set& s) const ;
    bool equal(const Set& b) const override;

    bool operator >=(const Set& o) const ;
    bool operator <=(const Set& o) const ;

    virtual Set& Union(const Set& b) const = 0;
    virtual Set& Intersect(const Set& b) const = 0;
    virtual Set& Substract(const Set& b) const = 0;
};

class FunctionalSet : public virtual Set{
public:
    Set& Union(const Set& b) const override ;
    Set& Intersect(const Set& b) const override ;
    Set& Substract(const Set& b) const override ;
};

class SubSet : public virtual FunctionalSet{
public:
    const Set &Parent;
    SubSet(const Set &p);// : parent(p), func(f) {}
    bool Contains(const Element& e) const override ;//{return parent.Contains(e) && func(e);}
    virtual bool Filter(const Element& e) const = 0;
};
class RSubSet : public virtual SubSet {
protected:
    const RulePtr func;
public:
    RSubSet(const Set &p, const RulePtr f);// : parent(p), func(f) {}
    virtual bool Filter(const Element& e) const override ;//{return parent.Contains(e) && func(e);}
};

class IForAll {
public: virtual bool ForAll(const RulePtr& r) const = 0;
};
class IExists {
public: virtual bool Exists(const RulePtr& r) const = 0;
};

class Uniwersum : public Set, public IForAll, public IExists{
public:
    bool Contains(const Element& e) const override {return true;}
    bool Includes(const Set& s) const override {return true;}
    
    bool ForAll(const RulePtr& r) const override {return false;}
    bool Exists(const RulePtr& r) const override {return true;}

    Set& Union(const Set& b) const override {return (Set&)*this;}
    Set& Intersect(const Set& b) const override {return (Set&)b;}
    Set& Substract(const Set& b) const override {
        const RulePtr rule { [this, &b](const Element& e){ return !b.Contains(e); } };
        return *(new RSubSet(*this, rule));
    }
};

const Uniwersum* const Uniwerse = new const Uniwersum{};