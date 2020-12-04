#include <iostream>
#include <string>

using namespace std;

bool isprime(int h)
{
    if (h <= 1)
    {
        return false;
    }

    for (int i = 2; i < h / 2 + 1; ++i)
    {
        if (h % i == 0)
        {
            return false;
        }
    }
    return true;
}

bool judge(string s, int h)
{
    if (s == "divide_by_three")
    {
        return h % 3 == 0;
    }
    else if (s == "divide_by_four")
    {
        return h % 4 == 0;
    }
    else if (s == "divide_by_five")
    {
        return h % 5 == 0;
    }
    return isprime(h);
}

int main()
{
    int T;
    cin >> T;

    for (int i = 0; i < T; ++i)
    {
        string s;
        int h;
        cin >> h >> s;

        int area;
        int min = 999999;
        if (judge(s, h))
        {
            min = h;
            area = 0;
        }

        for (int j = 1; j <= 4; ++j)
        {
            if (judge(s, h + j) && min > h + j)
            {
                min = h + j;
                area = j;
            }
        }
        cout << area << endl;
    }

    return 0;
}