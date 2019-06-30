/**
 * C++ template meta-programming
 */

#include <iostream>
#include <string>
#include "tmp.hpp"

using namespace std;
using namespace tmp;
using namespace tmp::arith;

template<int N>
struct sum
{
    template<int i, int sum>
    struct Stat {
        using next = Stat<i+1, i + sum>;
        
        constexpr static int ri = i;
        constexpr static int val = sum;
    };

    template<typename Stat>
    struct Cond {
        constexpr static bool val = Stat::ri < N;
    };

    constexpr static int val = WHILE<Cond, Stat<0, 0>>::val;
};

template<int N, int M>
struct gcd
{
    template<int b, int q, int r>
    struct Stat {
        using next = Stat<r, b/r, b%r>;    
        constexpr static int rr = r;
        constexpr static int val = b;
    };

    template<int b, int q>
    struct Stat<b, q, 0> {
        using next = void;
        constexpr static int rr = 0;
        constexpr static int val = b;
    };

    template<typename Stat>
    struct Cond {
        constexpr static bool val = Stat::rr != 0;
    };

    constexpr static int val = IF< gt<N, M>::val, WHILE<Cond, Stat<M, N/M, N%M>>, WHILE<Cond, Stat<N, M/N, M%N>> >::val;
};

template<int i, int j>
void Swap(int *a)
{
    if (a[i] > a[j]) {
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
}

template<int i, int j>
struct IntBubbleSortOnce
{
    static void exec(int *a) 
    {
        Swap<i, j>(a);
        IntBubbleSortOnce<i+1, j>::exec(a);
    }
};

template<int j>
struct IntBubbleSortOnce<j, j>
{
    static void exec(int *a) {}
};


template<int n>
void IntBubbleSort(int *a)
{
    IntBubbleSortOnce<0, n-1>::exec(a);
    IntBubbleSort<n-1>(a);
}

template<>
void IntBubbleSort<0>(int *a)
{
}

struct A
{
    int value = 123;
};

struct B
{
    using value = int;
};

struct C
{
};

int main()
{
    Cons<int, Cons<string, Cons<double, NIL>>> a;

    // 0 + 1 + ... + 9
    // output: 45
    cout << sum<10>::val << endl;

    cout << gcd<20, 16>::val << endl;

    cout << gcd<16, 20>::val << endl;

    int arr[] = {1, 3, 9, 5, 3, 8, 10, 6};
    IntBubbleSort<sizeof(arr) / sizeof(int)> (arr);

    cout << "arr: ";

    for (auto & i : arr)
    {
        cout << i << ", ";
    }

    cout << endl;

    cout << is_has_value<A>::value << endl;
    cout << is_has_value<B>::value << endl;
    cout << is_has_value<C>::value << endl;

    cout << detector<A, has_value>::value << endl;
    cout << detector<B, has_value>::value << endl;
    cout << detector<C, has_value>::value << endl;

    return 0;
}