#include <iostream>

using namespace std;

/*
 * 变参模版函数，依靠递归展开
 * 注意下面变参模版函数参数的声明方式以及递归展开方式
 */
void print()
{
}

template<typename T, typename ...Args>
void print(T head, Args... rest)
{
    cout << head << endl;
    print(rest...);
}

template<typename T>
int sum(T a)
{
    return a;
}

template<typename T, typename ...Args>
int sum(T a, Args... rest)
{
    return a + sum<T>(rest...);
}

/**
 * 依靠逗号表达式展开, 这里其实需要注意的是背后的原理是初始化列表表达式以及逗号表达式的运算方式
 */
template<typename T>
void printarg(T a)
{
    cout << a << endl;
}

template<typename ...Args>
void expand(Args... args)
{
    int a[] = {(printarg(args), 0)...};
}

/**
 * 更优雅的写法(支持lambda函数直接作为printarg这个功能)
 */
template<typename F, typename ...Args>
void expand_ext(const F & func, Args&& ...args)
{
    auto i = initializer_list<int>{(func(std::forward<Args>(args)), 0)...};
}

/**
 * 变参模版类
 * 偏特化模版展开参数包
 */
template<typename First, typename ...Args>
struct Base
{
    static constexpr size_t value = Base<First>::value + Base<Args...>::value;
};

template<typename Last>
struct Base<Last>
{
    static constexpr size_t value = sizeof(Last);
};

/**
 * 继承方式展开参数包 (依赖展开计算的那种不太适合继承展开)
 */
template<typename First, typename ...Args>
struct Base_2 : Base_2<Args...> {};

template<typename Last>
struct Base_2<Last>
{
    static constexpr size_t value = sizeof(Last);
};


int main()
{
    print(1,2,3);
    print("piapiapia");
    print('a', "888", 100100, 1.1);

    cout << sum(10) << endl;
    cout << sum(1, 2, 3, 4, 10) << endl;

    expand(1, 2, 3);
    expand_ext([](auto i){cout << i << endl;}, 1, 2, "pia");

    cout << Base<int, float, char>::value << endl;
    cout << Base_2<int, float, char>::value << endl;
    return 0;
}