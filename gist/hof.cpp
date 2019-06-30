/**
 *  higher order function programming needs compose, curry and so on
 */

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;
using namespace std::placeholders;

/**
 * compose(f1, f2) === f1(f2(...))
 * 
 * Support variadic as well
 * 
 * Require: parameters must be unary functor
 */
template<typename F1, typename F2>
auto compose(F1 f1, F2 f2)
{
    return [=](auto && x) { return f1(f2(x)); };
}

template<typename F1, typename ...F>
auto compose(F1 f1, F ...funcs)
{
    return [=](auto && x){ return f1(compose(funcs...)(x)); };
}

/**
 * hof_and(f1, f2, f3) === f1(x) && f2(x) && f3(x)
 */
template<typename F>
auto hof_and(F f)
{
    return [=](auto && x) { return f(x); };
}

template<typename F1, typename ...F>
auto hof_and(F1 f1, F ...funcs)
{
    return [=](auto && x) { return f1(x) && hof_and(funcs...)(x); };
}

/**
 * function arguments trait
 */
template<typename>
struct FuncType;

template<typename R, typename A>
struct FuncType<R(A)>
{
    using arg_type = A;
    using ret_type = R;

    constexpr static size_t arg_num = 1;
};

template<typename R, typename A1, typename ...A>
struct FuncType<R(A1, A...)>
{
    using arg_type = A1;
    using ret_type = R;
    using args = FuncType<R(A...)>;

    constexpr static size_t arg_num = 1 + FuncType<R(A...)>::arg_num;
};

/**
 * Assume f(int x, int y, int z) and f(x, y, z) = result
 * Then curry(f) = g, g(x) = h, h(y) = p, p(z) = result
 */
#define PLACEHOLDER(n) _n
#define REPEAT(n, f) REPEAT_##n(f), f(n))
#define REPEAT_1(f) f(1)
#define REPEAT_2(f) f(1),f(2)
#define REPEAT_3(f) f(1),f(2),f(3)
#define REPEAT_4(f) f(1),f(2),f(3),f(4))

template<typename>
struct Curry;

template<typename R, typename A>
struct Curry<R(A)>
{
    Curry(std::function<R(A)> f): m_func(f) {}

    auto apply(const A & x)
    {
        return m_func(x);
    }

    auto operator() (const A & x)
    {
        return apply(x);
    }

private:
    std::function<R(A)>     m_func;
};

template<typename R, typename A1, typename ...A>
struct Curry<R(A1, A...)>
{
    Curry(std::function<R(A1, A...)> f): m_func(f) {}

    auto apply(const A1 & x)
    {
        return Curry<R(A...)>(std::function<R(A...)>([=](A... args) {
            return m_func(x, args...);
        }));
    }

    auto operator() (const A1 & x)
    {
        return apply(x);
    }

private:
    std::function<R(A1, A...)>      m_func;
};

template<typename R, typename ...A>
auto curry(std::function<R(A...)> && f)
{
    return Curry<R(A...)>(f);
}


int foo(int x, string y, float k)
{
    return 0;
}


int main()
{
    /** 
     * f(x) = x + 1
     * g(x) = x * 2
     * h(x) = x + 3
     * compose(f, g, h) = f(g(h(x))) = (x + 3) * 2 + 1
     */
    {
        auto f = compose([](int i){ return i + 1; }, [](int i){ return i * 2; }, [](int i) { return i + 3; });
        assert (f(1) == 9);
        assert (f(2) == 11);
        assert (f(4) == 15);
        assert (f(10) == 27);
    }

    {
        auto f = hof_and([](int i){ return i!=0; }, [](int i){ return i%2==0; }, [](int i){ return i>10; });
        assert (f(12));
        assert (! f(9));
        assert (! f(8));
        assert (! f(-2));
    }

    {
        auto f = [](int x, string y, float k)->int {return 0;};
        typename FuncType<decltype(foo)>::arg_type i = 123;

        cout << FuncType<decltype(foo)>::arg_num << endl;
    }

    auto f2 = [](int x, int y, int z) { return x + y + z; };
    auto g2 = curry(std::function<int(int, int, int)>(f2));
    auto h2 = g2(1);
    cout << typeid(h2).name() << endl;
    auto p2 = h2(2);
    auto r = p2(3);
    cout << r << endl;
    return 0;
}