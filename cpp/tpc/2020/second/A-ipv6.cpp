#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

void string_split(const std::string &s, const char delim,
                  std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.emplace_back(item);
    }
}

string expand(const string &s)
{
    stringstream ss;
    vector<string> elems;
    vector<string> result;
    string_split(s, ':', elems);

    bool has_filled = false;
    int double_colons_idx = -1;
    for (int i = 0; i < elems.size(); ++i)
    {
        auto &v = elems[i];
        if (v.empty())
        {
            if (!has_filled)
            {
                int not_empty_size = 0;
                for (auto &t : elems)
                {
                    if (!t.empty())
                    {
                        not_empty_size++;
                    }
                }
                for (int j = 0; j < 8 - not_empty_size; ++j)
                {
                    result.push_back("0000");
                }
                has_filled = true;
            }
        }
        else
        {
            if (v.size() < 4)
            {
                v.insert(0, 4 - v.size(), '0');
            }
            result.push_back(v);
        }
    }

    for (int i = 0; i < result.size(); ++i)
    {
        if (i == 0)
        {
            ss << result[i];
        }
        else
        {
            ss << ":" << result[i];
        }
    }
    return ss.str();
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; ++i)
    {
        string s;
        cin >> s;
        cout << expand(s) << endl;
    }
}