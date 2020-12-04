#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    int T;
    cin >> T;

    for (int i = 0; i < T; ++i)
    {
        string s;
        cin >> s;

        int count_zero = 0;
        for (auto &c : s)
        {
            if (c == '0')
            {
                ++count_zero;
            }
        }

        int count_one = s.length() - count_zero;

        if (count_one == 0)
        {
            cout << "Impossible" << endl;
        }
        else if (count_zero > 2)
        {
            cout << "Impossible" << endl;
        }
        else if (count_zero == 1)
        {
            for (int j = 0; j < s.length(); ++j)
            {
                if (s[j] == '1')
                {
                    cout << s[j];
                }
            }
            cout << "0" << endl;
        }
        else if (count_zero == 2)
        {
            for (int j = 0; j < s.length(); ++j)
            {
                if (s[j] == '1')
                {
                    cout << s[j];
                }
            }
            cout << "00" << endl;
        }
        else
        {
            cout << s << endl;
        }
    }
    return 0;
}