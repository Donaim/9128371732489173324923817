#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <vector>

#include "set.cpp"
#include "fset.cpp"
#include "orderedset.cpp"
#include "kartesianProduct.cpp"
#include "relation.cpp"

#include "initializator.cpp"
#include "generator.cpp"
#include "exceptions.cpp"

#include "naturals.cpp"

using namespace std;

#define test(name) void name () { cout << endl << endl << QUOTE(name) << endl;

// void testFiniteContains(){
//     Initial init;
//     init.AddCustom(100);
//     init.AddCustom(200);
//     init.Add(Natural{100});
//     init.Add(Natural{200});
//     init.Add(Natural{-1});
//     init.AddCustom('c');
//     // init.AddCustom(init);
//     const FiniteSet set{init};

//     cout << set.Contains(Natural{1}) << endl;
//     cout << set.Contains(Natural{100}) << endl;
//     cout << set.Contains(Natural{2}) << endl;
//     cout << set.Contains(Natural{333}) << endl;
// }

// void testFiniteIncludes(){
//     Initial i1;
//     i1.AddCustom(3);
//     i1.AddCustom(6);
//     i1.Add(Natural{3});
//     i1.Add(Natural{4});
//     i1.AddCustom('a');
//     const FiniteSet set1{i1};

//     Initial i2;
//     i2.AddCustom(3);
//     i2.Add(Natural{4});
//     // i2.AddCustom(4);
//     const FiniteSet set2{i2};

//     cout << (set1.Includes(set2)) << endl;
//     cout << (set2.Includes(set1)) << endl;
//     cout << (set1 == set2) << endl; //double includes
// }

// void testPrinting(){
//     Initial i1;
//     i1.AddCustom(3);
//     i1.AddCustom(6);
//     i1.Add(Natural{3});
//     i1.Add(Natural{4});
//     i1.AddCustom('a');
//     const FiniteSet set1{i1};

//     Initial i2;
//     i2.AddCustom(3);
//     i2.Add(Natural{4});
//     // i2.AddCustom(4);
//     i2.Add(set1);
//     const FiniteSet set2{i2};
    
//     cout << set2 << endl;
// }

// void testFiniteSum(){
//     Initial i1;
//     // i1.AddCustom(3);
//     // i1.AddCustom(6);
//     i1.Add(Natural{3});
//     i1.Add(Natural{4});
//     // i1.AddCustom('a');
//     const FiniteSet set1{i1};

//     Initial i2;
//     // i2.AddCustom(3);
//     i2.Add(Natural{4});
//     i2.Add(Natural{7});
//     // i2.AddCustom(4);
//     i2.Add(set1);
//     const FiniteSet set2{i2};
    
//     cout << set1 << endl;
//     cout << set2 << endl;
//     cout << (FiniteSet&)(set1.Sum(set2)) << endl;
// }

// void testFiniteIntersect(){
//     Initial i1;
//     // i1.AddCustom(3);
//     // i1.AddCustom(6);
//     i1.Add(Natural{3});
//     i1.Add(Natural{4});
//     // i1.AddCustom('a');
//     const FiniteSet set1{i1};

//     Initial i2;
//     // i2.AddCustom(3);
//     i2.Add(Natural{4});
//     i2.Add(Natural{7});
//     // i2.AddCustom(4);
//     i2.Add(set1);
//     const FiniteSet set2{i2};
    
//     cout << set1 << endl;
//     cout << set2 << endl;
//     cout << (FiniteSet&)(set1.Intersect(set2)) << endl;
// }
// void testFiniteInfiniteIntersect(){
//     Initial i1;
//     i1.AddCustom(3);
//     i1.AddCustom(6);
//     i1.Add(Natural{3});
//     i1.Add(Natural{4});
//     i1.AddCustom('a');
//     const FiniteSet set1{i1};

//     const Naturals set2{};
    
//     cout << set1 << endl;
//     // cout << set2 << endl;
//     cout << (FiniteSet&)(set1.Intersect(set2)) << endl;
// }
// void testGeneratorFiniteInfiniteIntersect(){
//     FiniteSet set = Naturals{}.Generate(GenParams{0, 100, 500, 1000, 0});
// 	cout << set << endl;

//     RSubSet sub{set, RulePtr{[&set](const Element& e)
//     {
//         auto x = ToType<const Natural*>(&e);
//     	return true;
//     }}};
    
//     // cout << (FiniteSet&)set.Intersect(sub) << endl;
// }

// void testFiniteInfiniteSubstract(){
//     Initial i1;
//     i1.AddCustom(3);
//     i1.AddCustom(6);
//     i1.Add(Natural{3});
//     i1.Add(Natural{4});
//     i1.AddCustom('a');
//     const FiniteSet set1{i1};

//     const Naturals set2{};
    
//     cout << set1 << endl;
//     // cout << set2 << endl;
//     cout << (FiniteSet&)(set1.Substract(set2)) << endl;
// }

// class AELEMENT : public virtual Element, public virtual IComparable<Natural>, public IPrintable {
// public:
//     AELEMENT(char c){}
//     bool equal(const Natural& a, const Natural& b) const override {return false;} 
//     void Print(ostream& os) const override { os << "a"; }
// };
// class ACLASS : public FunctionalSet {
// public:
//     ACLASS() : ISizeable(-1) {}
//     bool Contains(const Element& e) const override { return IsTypeOf<AELEMENT>(&e); }
// };
// void testFiniteIntersect_InfiniteSumInfinite(){
//     const Naturals set2{};
//     const ACLASS set3{};
//     const Set& sum = set2.Sum(set3);
    
//     Initial i1;
//     i1.AddCustom(3);
//     i1.AddCustom(6);
//     i1.Add(Natural{3});
//     i1.Add(Natural{4});
//     i1.Add(AELEMENT{'a'});
//     i1.Add(sum);
//     const FiniteSet set1{i1};

//     cout << set1 << endl;
//     // cout << set2 << endl;
//     cout << (FiniteSet&)(set1.Intersect(sum)) << endl;
// }

// void testGenerator(){
//     auto set = Naturals{}.Generate(GenParams{1, 1000, 1000, 2000, 100});
//     cout << set << endl;
// }

// bool isDiv(const Element& e){
//     auto n = ToType<const Natural*>(&e);
//     return n->X % 2 == 0;
// }
// void testDivisionExample(){
//     Naturals N{};
//     RSubSet divis{N, RulePtr { [](const Element& e) { return isDiv(e); }}};
//     RSubSet d3{N, RulePtr { [](const Element& e) { return ToType<const Natural*>(&e)->X % 3 == 0; }}};
//     FiniteSet set = Naturals{}.Generate(GenParams{1, 1000, 1000, 2000, 100});
//     cout << (FiniteSet&)set.Intersect(divis.Intersect(d3)) << endl;
// }
// void testQuantifikatorExample(){
//     // Naturals N{};
//     // RSubSet divis{N, RulePtr { [](const Element& e) { return isDiv(e); }}};
//     FiniteSet set = Naturals{}.Generate(GenParams{1, 1000, 1000, 2000, 100});
//     RSubSet sub{set, RulePtr{[&set](const Element& e)
//         {
//             auto n = ToType<const Natural*>(&e);
//             return set.Exists(RulePtr { [n](const Element& x) { return ToType<const Natural*>(&x)->X * n->X == 10; }});
//     }}};
    
//     // cout << (FiniteSet&)sub << endl;
//     cout << (set.Count()) << endl;
//     cout << (FiniteSet&)set.Intersect(sub) << endl;
// }
test(testPrimeQuantifikatorExample)
    FiniteSet set = Naturals{}.Generate(GenParams{1, 200, 500, 1000, 0});
    RSubSet sub{set, RulePtr{[&set](const Element& e)
    {
        auto x = Natural::C(e);
        return set.ForAll(RulePtr { [&set, x](const Element& aa) 
        {
            auto a = Natural::C(aa);
            return set.ForAll(RulePtr { [&set, x, a](const Element& bb) 
            {
                auto b = Natural::C(bb);
                if(a * b == x) { return a == 1 || b == 1; } // a * b = x => a = 1 || b = 1
                else { return true; }
            }});
        }});
    }}};
    
    cout << conv<IPrintable>(set.Intersect(sub)) << endl;
}

test(testOddExample)
    FiniteSet set = Naturals{}.Generate(GenParams{1, 500, 500, 1000, 0});
    RSubSet sub{set, RulePtr{[&set](const Element& e)
    {
        auto x = Natural::C(e);
        return set.Exists(RulePtr { [&set, x](const Element& aa) 
        {
            auto a = Natural::C(aa);
            return 2 * a == x;
        }});
    }}};
    
    cout << conv<IPrintable>(set.Intersect(sub)) << endl;
}

test(testKartesianProduct)
    const FiniteOrderedSet set1 = Naturals{}.Generate(GenParams{1, 3, 500, 1000, 0});
    const FiniteOrderedSet set2 = Naturals{}.Generate(GenParams{4, 3, 500, 1000, 0});
    // cout << "set1.Count() = " << set1.Count() << endl;
    // cout << "set2.Count() = " << set2.Count() << endl;
    
    auto k1 = *new FiniteKartesianPSet(set1, set2);
    auto k2 = *new FiniteKartesianPSet(set2, set1);

    cout << k1 << endl;
    // cout << conv<FiniteSet>(set1.Union(set2)) << endl;
    // cout << (k1 == k2) << endl;
}

class MyRel : public PairRelation {
public:
    MyRel(const KartesianProduct &kp) : PairRelation(kp), SubSet(kp), Relation(kp) {}

    virtual bool Defines(const Element &a, const Element &b) const override {
        int x = Natural::C(a);
        int y = Natural::C(b);

        // return x <= y;
        return x % y == 0;
        // return (x + y) % 2 == 0;
        // return x == y - 1;
    }
};

test(testRelationDomain)
    const FiniteSet set1 = Naturals{}.Generate(GenParams{1, 5, 500, 1000, 0});
    const FiniteSet set2 = Naturals{}.Generate(GenParams{1, 5, 500, 1000, 0});
    
    auto k1 = *new FiniteKartesianPSet(set1, set2);

    MyRel mr{k1};
    // const Set& dom = mr.Domain();
    // const Set& range = mr.Range();

    auto pf = mr.PairForm();

    // cout << conv<FiniteSet>(set1.Intersect(dom)) << endl;
    // cout << conv<FiniteSet>(set2.Intersect(range)) << endl;
    cout << pf << endl;
}

test(testRelationProps)
    const FiniteOrderedSet set1 = Naturals{}.Generate(GenParams{1, 10, 500, 1000, 0});
    // const FiniteSet set2 = Naturals{}.Generate(GenParams{5, 50, 500, 1000, 0});
    
    auto k1 = *new FiniteKartesianPSet(set1, set1);
    // cout << k1 << endl;

    MyRel mr{k1};

    cout << "IsReflexive  : " << mr.IsReflexive() << endl;
    cout << "IsSymmetric  : " << mr.IsSymmetric() << endl;
    cout << "IsTransitive : " << mr.IsTransitive() << endl;
    cout << "IsTotal      : " << mr.IsTotal() << endl;
    cout << "IsAsymmetric : " << mr.IsAsymmetric() << endl;

    // cout << mr.IsEquivalence() << endl;
    // cout << mr.IsPartialOrder() << endl;
}

test(testExceptions)
    throw new SetEx("Hi there!");
}

test(testFiniteOrderedPair)
    const FiniteOrderedSet set1 = Naturals{}.Generate(GenParams{1, 3, 500, 1000, 0});
    const FiniteOrderedSet set2 = Naturals{}.Generate(GenParams{4, 3, 500, 1000, 0});
    // cout << "set1.Count() = " << set1.Count() << endl;
    // cout << "set2.Count() = " << set2.Count() << endl;
    
    auto k1 = *new FinitePairProduct(set1, set2);
    auto k2 = *new FinitePairProduct(set2, set1);

    cout << k1 << endl;
    // cout << k2 << endl;
    // cout << (k1 == k2) << endl;
    // cout << conv<FiniteSet>(set1.Union(set2)) << endl;
}

////////////////////////////////////////////////////////

void go_test() {
    // testFiniteContains();
    // testFiniteIncludes();
    // testPrinting();
    // testFiniteSum();
    // testFiniteIntersect();
    // testFiniteInfiniteIntersect();
    // testFiniteInfiniteSubstract();
    // testFiniteIntersect_InfiniteSumInfinite();    
    // testGenerator();
    // testDivisionExample();
    // testQuantifikatorExample();
    // testPrimeQuantifikatorExample();
    // testGeneratorFiniteInfiniteIntersect();
    // testOddExample();
    // testKartesianProduct();
    testRelationDomain();
    // testRelationProps();
    // testExceptions();
    // testFiniteOrderedPair();
}
