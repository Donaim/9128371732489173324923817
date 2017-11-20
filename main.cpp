#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <vector>

#include "set.cpp"
#include "naturals.cpp"
#include "initializator.cpp"

#include "test.cpp"

using namespace std;

int main(void){

    testFiniteContains();
    testFiniteIncludes();

    return 0;
}