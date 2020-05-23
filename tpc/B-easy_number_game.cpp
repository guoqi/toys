#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

using namespace std;

/*
void compose(vector<vector<int>> &C, vector<int> &s, const vector<int> &v, const set<int> &avail, int cn)
{
    if (cn <= 0)
    {
        C.push_back(s);
        s.erase(s.end() - 1);
        return;
    }

    cout << "hhh" << endl;

    for (auto &i : avail)
    {
        for (auto &j : avail)
        {
            if (i == j)
            {
                continue;
            }
            set<int> t = avail;
            t.erase(i);
            t.erase(j);
            s.push_back(v[i] * v[j]);
            compose(C, s, v, t, cn - 1);
        }
    }
}
*/

vector<int> compose();

int process(const vector<int> &v, int m)
{
    vector<vector<int>> C;
    vector<int> s;
    set<int> avail;
    int cn = v.size() * (v.size() - 1) / 2 / 2;

    cout << cn << endl;

    for (int i = 0; i < v.size(); ++i)
    {
        avail.insert(i);
    }

    for (auto &i : avail)
    {
        cout << i << " ";
    }
    cout << endl;

    compose(C, s, v, avail, cn);

    int min = 99999;

    for (auto &s : C)
    {
        for (auto &i : s)
        {
            cout << i << " ";
        }
        cout << endl;
        sort(s.begin(), s.end());
        int acc = accumulate(s.begin(), s.begin() + m + 1, 0, [](int a, int b) { return a + b; });
        if (min > acc)
        {
            min = acc;
        }
    }
    return min;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i)
    {
        int n, m;
        vector<int> a;
        cin >> n >> m;
        a.resize(n);

        for (int j = 0; j < n; ++j)
        {
            cin >> a[j];
        }

        cout << process(a, m) << endl;
    }
}