#ifndef __TEMPLATE_META_PROGRAMMING_H__
#define __TEMPLATE_META_PROGRAMMING_H__

#include <type_traits>
#include <typeinfo>
#include <iostream>

namespace tmp
{

/**
 * Linked-List of type
 */
template<typename Head, typename Tail>
struct Cons
{
    using car = Head;
    using cdr = Tail;
};

#define NIL void

namespace trait
{

    /**
     * type traits
     */
    template<typename T>
    struct is_void
    {
        static constexpr int val = 0;
    };

    template<>
    struct is_void<void>
    {
        static constexpr int val = 1;
    };

}

/*
template<typename T>
struct show_type
{
    using val = T;

    void operator() () 
    {
        std::cout << typeid(val).name() << std::endl;
    }

    void run()
    {
        std::cout << typeid(val).name() << std::endl;
    }
};
*/

namespace arith
{
    /**
     * arithmethic
     */
    template<int N, int M>
    struct add
    {
        static constexpr int val = N + M;
    };

    template<int N, int M>
    struct sub
    {
        static constexpr int val = N - M;
    };

    template<int N, int M>
    struct mul
    {
        static constexpr int val = N * M;
    };

    template<int N, int M>
    struct div
    {
        static constexpr int val = N / M;
    };

    template<int N, int M>
    struct mod
    {
        static constexpr int val = N % M;
    };

    /**
     * logic computing
     */
    template<int N, int M>
    struct lt 
    {
        static constexpr bool val = N < M;
    };

    template<int N, int M>
    struct gt 
    {
        static constexpr bool val = N > M;
    };

    template<int N, int M>
    struct _and
    {
        static constexpr bool val = N && M;
    };

    template<int N, int M>
    struct _or
    {
        static constexpr bool val = N || M;
    };

    template<int N>
    struct _not
    {
        static constexpr bool ret = ! N;
    };

}

/**
 * Control structures
 */
template<bool, typename T, typename F>
struct IF {};

template<typename T, typename F>
struct IF<true, T, F>
{
    constexpr static int val = T::val;
};

template<typename T, typename F>
struct IF<false, T, F>
{
    constexpr static int val = F::val;
};

template<typename Statement>
struct STOP
{
    constexpr static int val = Statement::val;
};

/**
 * Cond depends on Stat, and Stat must define next and ret members
 */
template<template<typename> class Cond, typename Stat>
struct WHILE
{
    constexpr static int val = IF<Cond<Stat>::val, WHILE<Cond, typename Stat::next>, STOP<Stat>>::val;
};


/**
 * trait example
 * Notice: void_t is required and it forces compiler to substitute its parameter. 
 * It can be fail if type T has no member type named value, and success verse vice. This is so-called SFINAE
 */
template<typename T, typename = std::void_t<>>
struct is_has_value : std::false_type {};
template<typename T>
struct is_has_value<T, std::void_t<typename T::value>> : std::true_type {};

/**
 * A common trait detector
 * It has the same structure as is_has_value but detect not only whether T has a member type named value, but also any attribute T must meet.
 */
template<typename T, template<typename> class Op, typename = std::void_t<>>
struct detector : std::false_type {};
template<typename T, template<typename> class Op>
struct detector<T, Op, std::void_t<Op<T>>> : std::true_type {};

template<typename T>
using has_value = typename T::value;

}

#endif