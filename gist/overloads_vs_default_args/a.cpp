#include <iostream>
#include "a.h"

using namespace std;

void foo(int a, int b = 100)
{
    cout << "print hhh" << endl;
    cout << a * b << endl;
}
