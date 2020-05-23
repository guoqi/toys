#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool is_lucky(const std::string &s)
{
    return s.find("TPC") != string::npos;
}

int reverse(string &s)
{
    vector<int> p_poss;
    int p_pos = 0;
    do
    {
        p_pos = s.find("P", p_pos);
    } while (p_pos != string::npos);
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i)
    {
        int n;
        cin >> n;
        string s;
        cin >> s;

        if (is_lucky(s))
        {
            cout << 0 << endl;
        }
        else
        {
        }
    }
}