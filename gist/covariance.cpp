#include <functional>
#include <iostream>

using namespace std;

struct Animal {};
struct Mammal : public Animal {};
struct Cat : public Mammal {};

Cat * foo1(Animal * a) { return nullptr; }

Animal * foo2(Animal * a) { return nullptr; }

Cat * foo3(Cat * m) {}

void test(std::function<Mammal*(Mammal*)> f)
{
}


int main()
{
    test(foo1);     // ok
    test(foo2);     // error
    test(foo3);     // error
    return 0;
}
