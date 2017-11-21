#pragma once

#include <iostream>
#include <cstdint>
#include <typeinfo>
#include <typeindex>

using namespace std;

class Element {
public:
    virtual bool operator ==(const Element& other) const = 0;
};

class UniqueElement : public Element{
public:
    bool operator ==(const Element& other) const override {return false;}
    template <typename T> bool operator ==(const T other) const {return false;}
};
class CommonElement : public Element{
public:
    bool operator ==(const Element& other) const override {return true;}
    template <typename T> bool operator ==(const T other) const {return true;}
};
