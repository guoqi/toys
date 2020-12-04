#include <iostream>

using namespace std;

template <int... Is> struct index {
  // static void print() { {(cout << Is, 0)...}; }
};

template <int N, int... Is> struct seq : seq<N - 1, N - 1, Is...> {};

template <int... Is> struct seq<0, Is...> : index<Is...> {};

int main() {
  using A = seq<5>;
  using B = seq<4, 4, 5>;
  using C = seq<3, 3, 4, 5>;
  using D = seq<2, 2, 3, 4, 5>;
  using E = seq<1, 1, 2, 3, 4, 5>;
  using F = seq<0, 0, 1, 2, 3, 4, 5>;
  using G = index<0, 1, 2, 3, 4, 5>;

  // G::print();

  cout << (std::is_base_of<G, A>::value ? "true" : "false") << endl;

  return 0;
}