#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

bool judge(const vector<int> &v)
{
    if (v.empty())
    {
        return true;
    }
    return std::all_of(v.begin(), v.end(), [&](int i) { return i == v[0]; });
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i)
    {
        int num;
        vector<int> v;
        cin >> num;
        v.resize(num);
        for (int j = 0; j < num; ++j)
        {
            cin >> v[j];
        }

        while (!judge(v))
        {
            std::sort(v.begin(), v.end());
            int t = v[num - 1] - v[0];
            v[0] = t;
            v[num - 1] = t;
        }

        cout << v[0] << endl;
    }
}