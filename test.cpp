#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <vector>

#include "set.cpp"
#include "naturals.cpp"
#include "initializator.cpp"
#include "generator.cpp"
#include "orderedset.cpp"
// #include "kartesian.cpp"

using namespace std;

void testFiniteContains(){
    Initial init;
    init.AddCustom(100);
    init.AddCustom(200);
    init.Add(Natural{100});
    init.Add(Natural{200});
    init.Add(Natural{-1});
    init.AddCustom('c');
    // init.AddCustom(init);
    const FiniteSet set{init};

    cout << set.Contains(Natural{1}) << endl;
    cout << set.Contains(Natural{100}) << endl;
    cout << set.Contains(Natural{2}) << endl;
    cout << set.Contains(Natural{333}) << endl;
}

void testFiniteIncludes(){
    Initial i1;
    i1.AddCustom(3);
    i1.AddCustom(6);
    i1.Add(Natural{3});
    i1.Add(Natural{4});
    i1.AddCustom('a');
    const FiniteSet set1{i1};

    Initial i2;
    i2.AddCustom(3);
    i2.Add(Natural{4});
    // i2.AddCustom(4);
    const FiniteSet set2{i2};

    cout << (set1.Includes(set2)) << endl;
    cout << (set2.Includes(set1)) << endl;
    cout << (set1 == set2) << endl; //double includes
}

void testPrinting(){
    Initial i1;
    i1.AddCustom(3);
    i1.AddCustom(6);
    i1.Add(Natural{3});
    i1.Add(Natural{4});
    i1.AddCustom('a');
    const FiniteSet set1{i1};

    Initial i2;
    i2.AddCustom(3);
    i2.Add(Natural{4});
    // i2.AddCustom(4);
    i2.Add(set1);
    const FiniteSet set2{i2};
    
    cout << set2 << endl;
}

void testFiniteSum(){
    Initial i1;
    // i1.AddCustom(3);
    // i1.AddCustom(6);
    i1.Add(Natural{3});
    i1.Add(Natural{4});
    // i1.AddCustom('a');
    const FiniteSet set1{i1};

    Initial i2;
    // i2.AddCustom(3);
    i2.Add(Natural{4});
    i2.Add(Natural{7});
    // i2.AddCustom(4);
    i2.Add(set1);
    const FiniteSet set2{i2};
    
    cout << set1 << endl;
    cout << set2 << endl;
    cout << (FiniteSet&)(set1.Sum(set2)) << endl;
}

void testFiniteIntersect(){
    Initial i1;
    // i1.AddCustom(3);
    // i1.AddCustom(6);
    i1.Add(Natural{3});
    i1.Add(Natural{4});
    // i1.AddCustom('a');
    const FiniteSet set1{i1};

    Initial i2;
    // i2.AddCustom(3);
    i2.Add(Natural{4});
    i2.Add(Natural{7});
    // i2.AddCustom(4);
    i2.Add(set1);
    const FiniteSet set2{i2};
    
    cout << set1 << endl;
    cout << set2 << endl;
    cout << (FiniteSet&)(set1.Intersect(set2)) << endl;
}
void testFiniteInfiniteIntersect(){
    Initial i1;
    i1.AddCustom(3);
    i1.AddCustom(6);
    i1.Add(Natural{3});
    i1.Add(Natural{4});
    i1.AddCustom('a');
    const FiniteSet set1{i1};

    const Naturals set2{};
    
    cout << set1 << endl;
    // cout << set2 << endl;
    cout << (FiniteSet&)(set1.Intersect(set2)) << endl;
}
void testGeneratorFiniteInfiniteIntersect(){
    FiniteSet set = Naturals{}.Generate(GenParams{0, 100, 500, 1000, 0});
	cout << set << endl;

    SubSet sub{set, RulePtr{[&set](const Element& e)
    {
        auto x = ToType<const Natural*>(&e);
    	return true;
    }}};
    
    // cout << (FiniteSet&)set.Intersect(sub) << endl;
}

void testFiniteInfiniteSubstract(){
    Initial i1;
    i1.AddCustom(3);
    i1.AddCustom(6);
    i1.Add(Natural{3});
    i1.Add(Natural{4});
    i1.AddCustom('a');
    const FiniteSet set1{i1};

    const Naturals set2{};
    
    cout << set1 << endl;
    // cout << set2 << endl;
    cout << (FiniteSet&)(set1.Substract(set2)) << endl;
}

class AELEMENT : public virtual Element, public virtual IComparable<Natural>, public IPrintable {
public:
    AELEMENT(char c){}
    bool equal(const Natural& a, const Natural& b) const override {return false;} 
    void Print(ostream& os) const override { os << "a"; }
};
class ACLASS : public FunctionalSet {
public:
    bool Contains(const Element& e) const override { return IsTypeOf<AELEMENT>(&e); }
};
void testFiniteIntersect_InfiniteSumInfinite(){
    const Naturals set2{};
    const ACLASS set3{};
    const Set& sum = set2.Sum(set3);
    
    Initial i1;
    i1.AddCustom(3);
    i1.AddCustom(6);
    i1.Add(Natural{3});
    i1.Add(Natural{4});
    i1.Add(AELEMENT{'a'});
    i1.Add(sum);
    const FiniteSet set1{i1};

    cout << set1 << endl;
    // cout << set2 << endl;
    cout << (FiniteSet&)(set1.Intersect(sum)) << endl;
}

void testGenerator(){
    auto set = Naturals{}.Generate(GenParams{1, 1000, 1000, 2000, 100});
    cout << set << endl;
}

bool isDiv(const Element& e){
    auto n = ToType<const Natural*>(&e);
    return n->X % 2 == 0;
}
void testDivisionExample(){
    Naturals N{};
    SubSet divis{N, RulePtr { [](const Element& e) { return isDiv(e); }}};
    SubSet d3{N, RulePtr { [](const Element& e) { return ToType<const Natural*>(&e)->X % 3 == 0; }}};
    FiniteSet set = Naturals{}.Generate(GenParams{1, 1000, 1000, 2000, 100});
    cout << (FiniteSet&)set.Intersect(divis.Intersect(d3)) << endl;
}
void testQuantifikatorExample(){
    // Naturals N{};
    // SubSet divis{N, RulePtr { [](const Element& e) { return isDiv(e); }}};
    FiniteSet set = Naturals{}.Generate(GenParams{1, 1000, 1000, 2000, 100});
    SubSet sub{set, RulePtr{[&set](const Element& e)
        {
            auto n = ToType<const Natural*>(&e);
            return set.Exists(RulePtr { [n](const Element& x) { return ToType<const Natural*>(&x)->X * n->X == 10; }});
    }}};
    
    // cout << (FiniteSet&)sub << endl;
    cout << set.Size << endl;
    cout << (FiniteSet&)set.Intersect(sub) << endl;
}
void testPrimeQuantifikatorExample(){
    FiniteSet set = Naturals{}.Generate(GenParams{1, 500, 500, 1000, 0});
    SubSet sub{set, RulePtr{[&set](const Element& e)
    {
        auto x = ToType<const Natural*>(&e);
        return set.ForAll(RulePtr { [&set, x](const Element& aa) 
        {
            auto a = ToType<const Natural*>(&aa);
            return set.ForAll(RulePtr { [&set, x, a](const Element& bb) 
            {
                auto b = ToType<const Natural*>(&bb);
                if(a->X * b->X == x->X) { return a->X == 1 || b->X == 1; }
                else { return true; }
            }});
        }});
    }}};
    
    // cout << (FiniteSet&)sub << endl;
    cout << (FiniteSet&)set.Intersect(sub) << endl;
}

void testOddExample(){
    FiniteSet set = Naturals{}.Generate(GenParams{1, 500, 500, 1000, 0});
    SubSet sub{set, RulePtr{[&set](const Element& e)
    {
        auto x = ToType<const Natural*>(&e);
        return set.Exists(RulePtr { [&set, x](const Element& aa) 
        {
            auto a = ToType<const Natural*>(&aa);
            return 2 * a->X == x->X;
        }});
    }}};
    
    // cout << (FiniteSet&)sub << endl;
    cout << (FiniteSet&)set.Intersect(sub) << endl;
}

void testFiniteOrderedSet(){
    // FiniteOrderedSet s{};
}

void testKartesianProduct(){
    const FiniteSet set1 = Naturals{}.Generate(GenParams{1, 3, 500, 1000, 0});
    const FiniteSet set2 = Naturals{}.Generate(GenParams{4, 3, 500, 1000, 0});
    
    cout << set1.KartesianProduct(set2) << endl; 
    cout << (set1.KartesianProduct(set2) == set2.KartesianProduct(set1)) << endl;
}