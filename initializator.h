#pragma once

#include <vector>

#include "set.cpp"
#include "staticElement.cpp"

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