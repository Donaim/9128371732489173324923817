#include <string>
#include <stdexcept>

using namespace std;

class TestClass : public std::runtime_error
{
    std::string what_message;
public:
    virtual const char* what() const throw() override
    {
        return what_message.c_str();
    }
};

