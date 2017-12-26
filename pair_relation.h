#pragma once

#include "set.h"
#include "fset.h"
#include "orderedset.h"
#include "kartesianProduct.h"
#include "util.cpp"
#include "relation.h"


class PairRelation : public virtual Relation {
    static const ISetCollection& GetCollection(const KartesianProduct &kp) ;

    PairRelation(const KartesianProduct &kProduct, const ISetCollection &scoll) ;
    PairRelation(const KartesianProduct &kProduct, const Set &x, const Set &y) ;

    const IForAll * const X_FA, * const Y_FA;
    const IExists * const X_IE, * const Y_IE;

public:
    const Set &X, &Y;
    PairRelation(const KartesianProduct &kProduct) ;

public:
    virtual bool Defines(const IOrderedSet &o) const ;
    virtual bool Defines(const Element &x, const Element &y) const = 0;

public: // parts
    const Set& Domain() const ;
    const Set& Range() const ;
    const FiniteSet & PairForm() const ;
public: //properties
    bool IsReflexive() const ;
    bool IsSymmetric() const ;
    bool IsTransitive() const ;
    bool IsTotal() const ;
    bool IsAsymmetric() const ;
    bool IsEquivalence() const ;
    bool IsPartialOrder() const ;
public: // abstraction
    const Set & AbstractionClass(const Element & e) const ;
    const FiniteSet & FunctionForm() const ;
};