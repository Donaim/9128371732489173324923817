#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <vector>

#include "base.cpp"
#include "naturals.cpp"
#include "initializator.cpp"

using namespace std;

class LUL{};

int main(void){
    //Element z{};
    //Naturals s{};

    //cout << ((Element)s).IsSet << endl; //ok
    //cout << IsTypeOf<Set>(&s) << endl; //ok
    //cout << IsTypeOf<LUL>(&z) << endl; //ok

    // RulePtr rule { [](const Element& e){ 
    //     auto n = dynamic_cast<const Natural*>(&e);
    //     return n && n->X % 2 == 0; 
    // }};
    //SubSet ss{s, rule};

    // const Element list[] =  { Natural{3}, StaticElement{"hehe"} };
    // const Element list2[] = { Natural{3}, StaticElement{"lul"}, StaticElement{"hehe"}, StaticElement{2} };
    
    // Element** list = new Element*[2];
    // auto n = Natural{3};
    // list[0] = &n;

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

    cout << set1.Contains(Natural{4}) << endl;
    cout << (set1.Includes(set2)) << endl;
    cout << (set2.Includes(set1)) << endl;
    cout << (set1 == set2) << endl;

    // list[0] = Natural{3};

    // const FiniteSet set{list, 2};
    // const FiniteSet set2{list2, 3};

    // // cout << set.Includes(set2) << endl;
    // cout << (set <= set2) << endl;

    // cout << ss.Contains(Natural{1}) << endl;
    // cout << ss.Contains(Natural{100}) << endl;
    // cout << ss.Contains(Natural{2}) << endl;
    // cout << ss.Contains(Natural{333}) << endl;


    return 0;
}