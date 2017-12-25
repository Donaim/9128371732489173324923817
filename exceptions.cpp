#pragma once

#include <string>
#include <stdexcept>

using namespace std;

class Set;
class Element;

class SetEx : public std::runtime_error
{
    const char * const what_message;
public:
    SetEx(const char* const str) : what_message(str), runtime_error(str) {} 

    virtual const char* what() const throw() override
    {
        return what_message;
    }
};

