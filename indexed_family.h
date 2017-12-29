#pragma once

#include "relation.h"
#include "pair_relation.h"


class IIndexed : public virtual Set {
public:
    virtual Set & Get(const Element & index) const = 0;
};
