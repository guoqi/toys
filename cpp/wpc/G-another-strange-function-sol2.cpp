#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define MAX  5 * 1000000 + 1

int (* M)[5 * 100000 + 1]; 

int strange(int j, int k)
{
    if (M[j][k] == MAX)
    {
        M[j][k] = std::min(strange(j, k-1), M[k][k]);
    }

    return M[j][k];
}

int main()
{
    M = new int [5 * 100000 + 1][5 * 100000 + 1];
    int T;
    cin >> T;
    for (int i=0; i<T; ++i)
    {
        string s;
        cin >> s;

        int n = s.length();

        for (int j=0; j<n; ++j)
        {
            for (int k=j; k<n; ++k)
            {
                if (j == k)
                {
                    M[j][k] = s[j] - 48;
                }
                else
                {
                    M[j][k] = MAX;
                }
            }
        }

        long long sum = 0;

        for (int j=0; j<n; ++j)
        {
            for (int k=j; k<n; ++k)
            {
                sum += strange(j, k);
            }
        }

        cout << sum << endl;
    }
    return 0;
}