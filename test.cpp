#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <vector>

#include "set.cpp"
#include "naturals.cpp"
#include "initializator.cpp"

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