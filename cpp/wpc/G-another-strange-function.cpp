#include <iostream>
#include <vector>
#include <map>

using namespace std;

map<int, map<int, int> > M;

int strange(int j, int k)
{
    if (M.find(j) == M.end() || M[j].find(k) == M[j].end())
    {
        M[j][k] = std::min(strange(j, k-1), M[k][k]);
    }

    return M[j][k];
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    cin >> T;
    for (int i=0; i<T; ++i)
    {
        M.clear();
        string s;
        cin >> s;

        int n = s.length();

        for (int j=0; j<n; ++j)
        {
            M[j][j] = s[j] - 48;
        }

        long long sum = 0;

        for (int j=0; j<n; ++j)
        {
            for (int k=j; k<n; ++k)
            {
                sum += strange(j, k);
            }
        }

        printf("%lld\n", sum);
    }
    return 0;
}