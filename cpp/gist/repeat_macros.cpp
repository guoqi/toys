#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

#define CONCAT(x, y) CONCAT_(x, y)
#define CONCAT_(x, y) x##y
#define CONCAT_ALTER(x, y) x##y
#define PLACEHOLDER(n) _n
#define REPEAT_CALL(f, ...) REPEAT_CALL_n(ARGS_COUNT(__VA_ARGS__), f)
#define REPEAT_CALL_n(n, f) CONCAT(REPEAT_CALL_, n)(f)
#define REPEAT_CALL_1(f) f(1)
#define REPEAT_CALL_2(f) REPEAT_CALL_1(f),f(2)
#define REPEAT_CALL_3(f) REPEAT_CALL_2(f),f(3)
#define REPEAT_CALL_4(f) REPEAT_CALL_3(f),f(4)

/**
 * 0 must be the first element and preprocessor will conjuct '(' with __VA_ARGS__ by mistake otherwise.
 * 
 * parameters count must be not larger than 22
 */
#define ARGS_COUNT(...) ARGS_COUNT_(0, ##__VA_ARGS__, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define ARGS_COUNT_(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, N, ...) N


void foo(int i)
{
    cout << i << endl;
}

int main()
{
    /**
     * Expand process:
     *     CONCAT(REPEAT_CALL_, 4)(foo)
     * ==> CONCAT_(REPEAT_CALL, 4)(foo)                 // CONCAT is a macro
     * ==> REPEAT_CALL_##4(f)                           // CONCAT_ is a macro
     * ==> REPEAT_CALL_4(foo)                           // ## conjucts two symbol into one
     * ==> REPEAT_CALL_3(foo), foo(4)                   // REPEAT_CALL_4 is a macro
     * ==> REPEAT_CALL_2(foo), foo(3), foo(4)           // REPEAT_CALL_3 is a macro
     * ==> REPEAT_CALL_1(foo), foo(2), foo(3), foo(4)   // REPEAT_CALL_2 is a macro
     * ==> foo(1), foo(2), foo(3), foo(4)               // REPEAT_CALL_1 is a macro
     */
    REPEAT_CALL_n(4, foo);

    REPEAT_CALL(foo, 1, 1, 1, 1);

    /**
     * Differences with CONCAT and CONCAT_ALTER:
     *      CONCAT could concat any tokens whatever it is.
     *      CONCAT_ALTER could only concat simple token and cauldn't process macros properly.
     * Macro expansions rules cause this difference. It obeys the rule as follows (from gcc online documeentations):
     *      Macro arguments are completely macro-expanded before they are substituted into a macro body, 
     *      unless they are stringized or pasted with other tokens. After substitution, the entire macro body, 
     *      including the substituted arguments, is scanned again for macros to be expanded. 
     *      The result is that the arguments are scanned twice to expand macro calls in them.
     */
    int CONCAT(a, 1) = 2;               // expand to `int a1 = 2;`  ok
    int CONCAT_ALTER(a, 2) = 2;         // expand to `int a2 = 2;`  ok

    #define B b
    int CONCAT(B, 1) = 2;               // expand to `int b1 = 2;`  ok
    int CONCAT_ALTER(B, 2) = 2;         // oops! Does it expand to `int b2 = 2;` ?

    // Let's try output this variable
    cout << a1 << endl;
    cout << a2 << endl;
    cout << b1 << endl;
    //cout << b2 << endl;               // oops! error: use of undeclared identifier 'b2'
    cout << B2 << endl;                 // It's ok. why?

    return 0;
}