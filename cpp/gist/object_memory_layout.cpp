#include <iostream>

using namespace std;

class Base {
public:
  Base() : a('A') {}
  virtual int foo() { return 89; };

public:
  char a;
};

class Devired : public Base {
public:
  Devired(int i) : b(i) {}
  virtual int foo() { return b; }

public:
  int b;
};

int main() {
  Devired c(1111);
  Base *p = &c;

  cout << sizeof(Base) << endl;
  cout << sizeof(Devired) << endl;
  cout << sizeof(int) << endl;
  cout << sizeof(char) << endl;
  cout << sizeof(long) << endl;
  cout << sizeof(char *) << endl;

  // cout << p->foo() << endl;

  for (int i = 0; i < 4; ++i) {
    printf("0x%x\n", *(int *)((int *)p + i));
  }

  cout << &Base::foo << endl;
  cout << &Devired::foo << endl;

  cout << "==========" << endl;

  cout << *(char *)((int *)p + 2) << endl;
  cout << *(int *)((int *)p + 3) << endl;

  cout << (long *)*(long *)p << endl;
  cout << (long *)*(long *)*(long *)p << endl;

  auto f = (int (*)())((long *)*(long *)*(long *)p);
  cout << f() << endl;

  return 0;
}
