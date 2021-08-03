#include <iostream>
#include <sstream>

using namespace std;

namespace tmp {

/**
 *
 */

template <int... Is> struct index {};

template <int N, int... Is> struct seq : seq<N - 1, N - 1, Is...> {};

template <int... Is> struct seq<0, Is...> : index<Is...> {};

/**
 *
 */

template <class T> struct type {};

template <class T, int N> struct type_N {};

} // namespace tmp

namespace internal {

template <typename T> T str_to(tmp::type<T>, const std::string &s) {
  std::stringstream ss(s);
  T t;
  ss >> t;
  return t;
}

template <> std::string str_to(tmp::type<std::string>, const std::string &s) {
  return s;
}

} // namespace internal

template <typename T> T str_to(const std::string &s) {
  return internal::str_to(tmp::type<T>(), s);
}

int main() {
  cout << str_to<int>("123") << endl;
  return 0;
}