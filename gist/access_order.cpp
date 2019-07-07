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

union helper {
    int A::* p;
    long offset;
};

template<typename A, typename data1, typename data2>
void access_order(data1 A::*mem1, data2 A::*mem2)
{
    helper p1 = helper{mem1};
    helper p2 = helper{mem2};
    string result = p1.offset > p2.offset ? "first occurs first"  : "first occurs second";
    cout << result << endl;
}

int main()
{
    access_order(&A::z, &A::y);
    access_order(&A::x, &A::y);
    return 0;
}