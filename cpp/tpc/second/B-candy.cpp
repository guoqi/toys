#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
    int n;
    string s;
    cin >> n >> s;
    map<int, int> candy_num;
    for (int i = 0; i < n; ++i)
    {
        int t;
        cin >> t;
        candy_num[t]++;
    }

    map<int, int> number_candy;
    int min_candy_number = 99999;
    for (auto &item : candy_num)
    {
        if (item.second > min_candy_number)
        {
            min_candy_number = item.second;
        }
        number_candy[item.second]++;
    }

    if (s == "Alice")
    {
        if (number_candy[1] > 0 || number_candy[2] > 0)
        {
            cout << "Alice" << endl;
        }
        else
        {
            cout << "Bob" << endl;
        }
    }
    else if (s == "Bob")
    {
        if (number_candy[1] > 0 || number_candy[2] > 1)
        {
            cout << "Alice" << endl;
        }
        else
        {
            cout << "Bob" << endl;
        }
    }

    return 0;
}