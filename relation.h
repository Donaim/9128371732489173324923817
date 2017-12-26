#pragma once

#include "set.h"
#include "fset.h"
#include "orderedset.h"
#include "kartesianProduct.h"
#include "util.cpp"

class Relation : public virtual SubSet {
public:
    const KartesianProduct &kProduct;
public:
    Relation(const KartesianProduct &kProduct) ;

    virtual bool Filter(const Element& e) const override ;

    virtual bool Defines(const IOrderedSet& o) const = 0;
};
