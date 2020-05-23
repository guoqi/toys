#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

bool is_prime(long long a, long long b)
{
    long long t = std::min(a, b);
    for (long long i = 2; i <= t; ++i)
    {
        if (a % i == 0 && b % i == 0)
        {
            return false;
        }
    }
    return true;
}

bool is_prime(const vector<long long> &v, long long i)
{
    return std::all_of(v.begin(), v.end(), [i](long long a) { return a == 1 || is_prime(i, a); });
}

long long find_groups(long long n)
{
    std::list<long long> a;
    for (long long i = 1; i <= n; ++i)
    {
        a.push_back(i);
    }

    long long count = 0;
    std::vector<long long> v;
    while (!a.empty())
    {
        count++;
        for (std::list<long long>::iterator it = a.begin(); it != a.end(); ++it)
        {
            if (is_prime(v, *it))
            {
                v.push_back(*it);
                a.erase(it);
            }
        }
        for (auto &item : v)
        {
            cout << item << " ";
        }
        cout << endl;
        v.clear();
    }

    return count;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i)
    {
        long long n;
        cin >> n;
        // cout << find_groups(n) << endl;
        if (n == 1)
        {
            cout << 1 << endl;
        }
        else
        {
            cout << n / 2 << endl;
        }
    }
}