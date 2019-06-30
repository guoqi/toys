#include <iostream>
#include <exception>

using namespace std;

void foo()
{
    throw runtime_error("opps");
}

int main()
try
{
    foo();
    return 0;
}
catch (exception & e)
{
    cout << e.what() << endl;
    return 1;
}
