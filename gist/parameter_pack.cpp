#include <iostream>
#include <string>

using namespace std;

template<int a, int ... args>
struct A1 {
    static constexpr int sum = a + A1<args...>::sum;
};

template<int a>
struct A1<a> {
    static constexpr int sum = a;
};

template<typename a, typename ... args>
struct A2 {
    static constexpr size_t size = sizeof(a) + A2<args...>::size;
};

template<typename a>
struct A2<a> {
    static constexpr size_t size = sizeof(a);
};

/*
template<typename class A, typename class ... args>
struct A3 {

};
*/

void foo()
{
    cout << "empty" << endl;
}

template<typename First, typename ... Args>
void foo(First first, Args ... args)
{
    cout << 1 + sizeof...(args) << endl;
    cout << typeid(first).name() << " " << first << endl;
    foo(args...);
}

int main()
{
    // output 56
    cout << A1<1, 2, 3, 10, 9, 8, 23>::sum << endl;

    // output 25
    cout << A2<int, float, bool, double, int *>::size << endl;
    cout << sizeof(float) << endl;
    cout << sizeof(bool) << endl;

    foo(1, 2, 3.0, true, "string");
    return 0;
}