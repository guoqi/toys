#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
struct NumberLike
{
    const static bool value = false;
};


template<>
struct NumberLike<int>
{
    const static bool value = true;
};

template<>
struct NumberLike<double>
{
    const static bool value = true;
};


template<typename T>
T mean(const vector<T> & vs)
{
    static_assert (NumberLike<T>::value == true, "type T must be NumberLike");

    auto it = vs.begin();
    auto r = *it;

    for (++it; it!=vs.end(); ++it)
    {
        r += *it;
    }

    return r / vs.size();
}

int main()
{
    vector<int> iv = {1, 2, 3, 4};
    vector<double> dv = {1.1, 2.2, 3.3, 4.4};
    vector<string> sv = {"1", "2", "3", "4"};
    cout << mean(iv) << endl;
    cout << mean(dv) << endl;
    //cout << mean(sv) << endl;
    return 0;
}
