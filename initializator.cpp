#pragma once

#include <vector>
#include "Element.h"
#include "initializator.h"
#include "util.cpp"

using namespace std;

void Initial::Add(const Element& e) 
{
    v.push_back(&e);
}

template <typename T>
void Initial::AddCustom(T x){
    const Element* e = new StaticElement{x};
    v.push_back(e);
}

const Element** Initial::Get() {
    return &v.front();
}

int Initial::size() {return v.size();}