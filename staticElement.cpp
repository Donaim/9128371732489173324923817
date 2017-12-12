#pragma once

#include <iostream>
#include "Element.h"
#include "util.cpp"

#define REPORT_CREATED false
#define EXPLICIT_ELEMENT_CREATION true

class StaticElement : public virtual Element, public virtual IComparable<StaticElement>, public IPrintable {
    const uint8_t* const obj;
    const int size;
    const size_t id;
    
    template <typename T>
    static uint8_t* cpy(T& p){
        uint8_t* start = (uint8_t*)&p;
        uint8_t* copy = new uint8_t[sizeof(p)];
        for(int i = 0; i < sizeof(p); i++) {copy[i] = start[i];}

        return copy;
    }
protected:
public:
    template <typename T> 
    explicit StaticElement(T x) : obj(cpy(x)), size(sizeof(x)), id(type_index(typeid(x)).hash_code()) 
    {
    #if REPORT_CREATED 
        reportCreated();
    #endif
    }

    void reportCreated() const {
        cout << "Created StaticElement: " << *this << ';' << endl;
    }
    void Print(ostream& os) const override {
        os << '[' << '|';
        for(int i = 0; i < size; i++){ os << (int)obj[i] << '|' ;}
        os << ']';
    }

    bool equal(const StaticElement& b) const override {
        if(
            this->size <= 0 || b.size <= 0
            || this->size != b.size
            || this->id != b.id
        ) {return false;}

        for(int i = 0; i < this->size; i++){
            if(this->obj[i] != b.obj[i]) {return false;}
        }
    }
};