#pragma once

#include "fset.h"
#include "orderedset.h"

bool IOrderedSet::Includes(const Set& s) const {
    const IOrderedSet* o = ToType<const IOrderedSet*>(&s);
    if(o)
    {
        // cout << o->Size << "vs" << this->Size << endl;
        if(o->Size > this->Size) {return false;}

        for(int i = 0, to = s.Size.Count(); i < to; i++){
            if(!(o->Get(i) == this->Get(i))) {return false;}
        }

        return true;
    }
    else { return false; }
}
void IOrderedSet::Print(ostream& os) const {
    if(Size.UndefinedQ()) { os << "(f->?)"; return; }
    else if(Size.InfiniteQ()) { os << "(∞)"; return; }
    else if(Size.EmptyQ()) { os << '(' << ')'; return; }

    os << '(';
    IPrintable::printElement(os, &Get(0));
    for(int i = 1, to = Size.Count(); i < to; i++) {
        os << ',';
        IPrintable::printElement(os, &Get(i));
    }

    os << ')';
}



const Element& FiniteOrderedSet::Get(int index) const 
{
    if(index > Size.Count()) { throw new SetEx("index is out of range!"); } 
    return *FiniteSet::list[index]; 
} 
void FiniteOrderedSet::Print(ostream& os) const { IOrderedSet::Print(os); }


const Element** OrderedPair::createPair(const Element &a, const Element &b) {
    const Element ** re = new const Element*[2];
    re[0] = &a;
    re[1] = &b;
    return re;
}
OrderedPair::OrderedPair(const Element **els) : FiniteOrderedSet(els, 2), FiniteSet(els, 2), ISizeable(2) {}
const Element& OrderedPair::A() const { return *FiniteSet::list[0]; }
const Element& OrderedPair::B() const { return *FiniteSet::list[1]; }
OrderedPair::OrderedPair(const Element &a, const Element &b) : OrderedPair(createPair(a, b)) {}



TmpPair::TmpPair() : x(nullptr), y(nullptr), ISizeable(2) {}
const Element& TmpPair::Get(int index) const {
    switch(index){
        case 0: return *x;
        case 1: return *y;
        default: throw new SetEx( "Index out of range 2 !");
    }
}
bool TmpPair::Contains(const Element& e) const { return *x == e || *y == e; }
bool TmpPair::equal(const Set &b) const {return equal((const Element&)b);}
bool TmpPair::equal(const Element &b) const {
    const IOrderedSet* o = ToType<const IOrderedSet*>(&b);

    if(o){
        if(o->Size != this->Size) {return false;}
        return o->Get(0) == *x && o->Get(1) == *y;
    }
    
    return false;
}
bool TmpPair::operator == (const Element &e) const { return equal(e); }




PairProduct::PairProduct(const IOrderedSet & a, const IOrderedSet & b) : A(a), B(b), ISizeable(a.Size) {
    if(a.Size != b.Size) { throw new SetEx("To create PairProduct sets must be of same size!"); }
}
bool PairProduct::Contains(const Element & e) const {
    const IOrderedSet* s = ToType<const IOrderedSet*>(&e);

    if(s){
        if(s->Size.Count() == 2) { // is pair
            return Contains(*new OrderedPair(s->Get(0), s->Get(1)));
        }
    }

    return false;
}
const Element & PairProduct::Get(int index) const {
    return *new OrderedPair(A.Get(index), B.Get(index));
}


// const Element** FinitePairProduct::getList(const FiniteOrderedSet & a, const FiniteOrderedSet & b) {
//     return (Element**)nullptr;
// }
// FinitePairProduct::FinitePairProduct(const FiniteOrderedSet & a, const FiniteOrderedSet & b) 
//     : PairProduct(a, b), FiniteOrderedSet(getList(a, b), a.Size), ISizeable(a.Size) 
// {

// }
// bool FinitePairProduct::Contains(const IOrderedSet & o) const {
//     return false;
// }
