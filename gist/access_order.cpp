#include <iostream>
#include <string>

using namespace std;

class A
{
public:
    int x;
    int y;
    int z;
};


template<typename A, typename data1, typename data2>
void access_order(data1 A::*mem1, data2 A::*mem2)
{
    auto p1 = mem1;
    auto p2 = mem2;
    string result = p1 > p2 ? "first occurs first"  : "first occurs second";
    cout << result << endl;
}

int main()
{
    access_order(&A::z, &A::y);
    return 0;
}