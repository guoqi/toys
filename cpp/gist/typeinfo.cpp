#include <iostream>
#include <typeinfo>

using namespace std;

namespace fund {

class A {};

} // namespace fund

int main() {
  fund::A a;
  cout << typeid(a).name() << endl;
  return 0;
}
