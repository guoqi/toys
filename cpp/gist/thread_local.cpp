#include <functional>
#include <iostream>
#include <memory>

using namespace std;

template <int I> class A {
public:
  void foo(int i) {
    thread_local int a = i;
    cout << a << endl;
  }
};

class B {
public:
  template <int N> B() { cout << N << endl; }
};

/*
template <int N> struct number : number<N - 1> {
  static constexpr int value = N;
};

template <> struct number<0> { static constexpr int value = 0; };

template <int N> constexpr int count(int R = number<N - 1>::value) { return R; }
*/

/*
template <int N> struct flag { friend constexpr int adl_flag(flag<N>); };

template <int N> struct writer {
  friend constexpr int adl_flag(flag<N>) { return N; }

  static constexpr int value = N;
};

template <int N, int = adl_flag(flag<N>{})> int constexpr reader(int, flag<N>) {
  return N;
}

template <int N>
int constexpr reader(float, flag<N>, int R = reader(0, flag<N - 1>{})) {
  return R;
}

int constexpr reader(float, flag<0>) { return 0; }

template <int N = 1>
int constexpr next(int R = writer<reader(0, flag<32>{}) + N>::value) {
  return R;
}
*/

template <typename T, int N> struct Test : public Test<T, N - 1> {
  static constexpr int value = N;
};

template <typename T> struct Test<T, 0> { static constexpr int value = 1; };

template <class T> struct wrapper {
  T *operator->() { return new T(); }
};

namespace fund {

namespace utils {

template <class From, class To> bool type_cast(const From &from, To &to);

template <class From, class To> struct TypeUtil {};

template <class From, class To> bool type_cast(const From &from, To *to) {
  return TypeUtil<From, To>::convert(from, to);
}

template <class T> struct type {};

template <class T, int N> struct type_N {};

} // namespace utils

} // namespace fund

namespace fund {

namespace utils {

template <class T, int N> struct ThreadVariables;

template <class T, int N> struct ThreadVariables<T *, N>;

namespace inner {

template <class T, typename... Args>
std::function<T *(Args...)> __default_creator() {
  return [](Args &&... args) {
    return new T(std::forward<Args>(std::forward<Args>(args))...);
  };
}

template <class T, typename Func, typename... Args>
std::function<T *(Args...)> __wrapper_creator(Func &&func) {
  return [func](Args &&... args) {
    return func(std::forward<Args>(std::forward<Args>(args))...);
  };
}

/**
 * FIXME: that's a trick from
 * https://www.fluentcpp.com/2017/08/15/function-templates-partial-specialization-cpp/
 *
 * Use function overload instead of function template partial specialization
 * because the later is not supported by compiler
 *
 * Argument type<T> is only for overload matching, otherwise this function
 * cannot be overloaded with different T in this situtation (T is the return
 * type, whether function overload only match arguments)
 */

template <class T, int N, typename... Args>
ThreadVariables<T, N> *__make_variable(type_N<T, N>, Args &&... args) {
  return new ThreadVariables<T, N>(inner::__default_creator<T, Args...>(),
                                   std::forward<Args>(args)...);
}

template <class T, int N, typename... Args>
ThreadVariables<T *, N> *__make_variable(type_N<T *, N>, Args &&... args) {
  return new ThreadVariables<T *, N>(inner::__default_creator<T, Args...>(),
                                     std::forward<Args>(args)...);
}

template <class T, int N, typename Func, typename... Args>
ThreadVariables<T, N> *__make_variable_f(type_N<T, N>, Func &&func,
                                         Args &&... args) {
  return new ThreadVariables<T, N>(
      inner::__wrapper_creator<T, Func, Args...>(std::forward<Func>(func)),
      std::forward<Args>(args)...);
}

template <class T, int N, typename Func, typename... Args>
ThreadVariables<T *, N> *__make_variable_f(type_N<T *, N>, Func &&func,
                                           Args &&... args) {
  return new ThreadVariables<T *, N>(
      inner::__wrapper_creator<T, Func, Args...>(std::forward<Func>(func)),
      std::forward<Args>(args)...);
}

} // namespace inner

template <class T> struct ThreadVariables<T, 0> {
  ThreadVariables() = default;

  T &operator->() { return this->forward(); }

  virtual T &forward() = 0;
};

template <class T> struct ThreadVariables<T *, 0> {
  ThreadVariables() = default;

  T *operator->() { return this->forward(); }

  virtual T *forward() = 0;
};

/**
 * thread-local variable wrapper. make it easier to use
 */
template <class T, int N>
struct ThreadVariables : public ThreadVariables<T, N - 1> {
  template <typename... Args>
  explicit ThreadVariables(std::function<T *(Args...)> &&func,
                           Args &&... args) {
    this->func_ = std::bind(std::forward<decltype(func)>(func),
                            std::forward<Args>(args)...);
    this->func_(); // 尝试初始化一下, 避免一些问题隐藏到执行时
  }

  ThreadVariables() = default;

  // direct forward, act like a global T * variable
  T &forward() override {
    thread_local std::unique_ptr<T> ins(func_());
    return *(ins.get());
  }

protected:
  std::function<T *()> func_;
};

/**
 * partial specialization for pointer type
 */
template <class T, int N>
struct ThreadVariables<T *, N> : public ThreadVariables<T *, N - 1> {
  template <typename... Args>
  explicit ThreadVariables(std::function<T *(Args...)> &&func,
                           Args &&... args) {
    this->func_ = std::bind(std::forward<decltype(func)>(func),
                            std::forward<Args>(args)...);
    this->func_(); // 尝试初始化一下, 避免一些问题隐藏到执行时
  }

  ThreadVariables() = default;

  // direct forward, act like a global T * variable
  T *forward() override {
    thread_local std::unique_ptr<T> ins(this->func_());
    return ins.get();
  }

protected:
  std::function<T *()> func_;
};

template <class T, typename... Args>
ThreadVariables<T, 0> *make_variable(Args &&... args) {
  return inner::__make_variable(type_N<T, 0>{}, std::forward<Args>(args)...);
}

template <class T, typename Func, typename... Args>
ThreadVariables<T, 0> *make_variable_f(Func &&func, Args &&... args) {
  return inner::__make_variable_f(type_N<T, 0>{}, std::forward<Func>(func),
                                  std::forward<Args>(args)...);
}

template <class T, int N, typename... Args>
ThreadVariables<T, 0> *make_variable_N(Args &&... args) {
  return inner::__make_variable(type_N<T, N>{}, std::forward<Args>(args)...);
}

template <class T, int N, typename Func, typename... Args>
ThreadVariables<T, 0> *make_variable_f_N(Func &&func, Args &&... args) {
  return inner::__make_variable_f(type_N<T, N>{}, std::forward<Func>(func),
                                  std::forward<Args>(args)...);
}

} // namespace utils

} // namespace fund

namespace fund {

namespace utils {

template <typename T> class pointer {
public:
  pointer(T *t) : ptr_(t) {}
  pointer() = default;

  pointer &operator=(T *t) {
    ptr_.reset(t);
    return *this;
  }

  T &operator->() { return *(ptr_.get()); }

private:
  pointer(const pointer<T> &that) = delete;
  pointer &operator=(const pointer<T> &&that) = delete;

private:
  std::unique_ptr<T> ptr_;
};

} // namespace utils

} // namespace fund

class Luck {
public:
  Luck() { cout << "luck! " << this << endl; }
  void wang() { cout << "wang~ " << this << endl; }

  Luck *operator->() { return this; }
};

using namespace fund::utils;

int main() {
  A<1> a;
  A<1> b;
  a.foo(1);
  b.foo(2);

  using LT = pointer<ThreadVariables<Luck, 0>>;

  std::function<Luck *()> init = []() { return new Luck(); };

  LT l1 = make_variable_f_N<Luck, 1>(init);
  LT l2 = make_variable_f_N<Luck, 2>(init);
  LT l3 = make_variable_f_N<Luck, 3>(init);
  LT l4 = make_variable_f_N<Luck, 1>(init);

  l1->wang();
  l2->wang();
  l3->wang();
  l4->wang();

  /*
    Test<int, 2> t2;
    Test<int, 1> t1;
    Test<int, 0> t0;

    cout << std::is_base_of<decltype(t0), decltype(t1)>::value << endl;
    cout << std::is_base_of<decltype(t1), decltype(t2)>::value << endl;
    cout << std::is_base_of<decltype(t0), decltype(t2)>::value << endl;

    int n = 10;
    int *t = &n;
    std::shared_ptr<int *> s(&t);

    s.operator->();

    B b1();
    B b2();
    */

  return 0;
}
