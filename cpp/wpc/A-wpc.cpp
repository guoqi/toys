#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main()
{
    int T;
    cin >> T;
    for (int i=0; i<T; ++i) 
    {
        int n;
        cin >> n;
        stringstream outss;
        for (int j=0; j<n; ++j)
        {
            string s;
            cin >> s;
            outss << (char)toupper(s[0]);
        }
        cout << outss.str() << endl;
    }

    return 0;
}