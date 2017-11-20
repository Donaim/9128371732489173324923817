#pragma once

#include "base.cpp"

#include <vector>

using namespace std;

class Initial{
    vector<const Element*> v;
public:
    void Add(const Element& e);

    template <typename T>
    void AddCustom(T x);

    const Element** Get() ;

    int size();
};