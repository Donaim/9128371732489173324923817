#pragma once

#include "Element.h"
#include "set.h"
#include "fset.h"

class OrderedSet : public virtual Set {

};


class FiniteOrderedSet : public virtual OrderedSet, public virtual FiniteSet {
    bool equal(const Set& a, const Set& b) const override;
};