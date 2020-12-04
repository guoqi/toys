#include <iostream>
#include <vector>

using namespace std;

void show(const vector< vector<int> > & array)
{
    cout << "result.size()=" <<  array.size() << endl;
    for (auto & vs : array)
    {
        for (auto & v : vs)
        {
            cout << v << " ";
        }
        cout << endl;
    }
}

// 前k个进行操作, 暴力得到结果列表
vector< vector<int> > do_operation(const vector<int> & array, int n, int start, int k)
{
    vector< vector<int> > result;

    for (int i=start; i<start+k; ++i)
    {
        vector<int> tmp (array.begin() + start + k, array.end());

        for (int j=i; j>=start; j--)
        {
            tmp.push_back(array[j]);
        }

        for (auto & v : do_operation(array, n, i+1, k-i))
        {
            vector<int> t(tmp);
            t.insert(t.end(), v.begin(), v.end());
            result.push_back(t);
        }
    }
    show(result);
    return result;
}

int main()
{
    int T;
    cin >> T;
    for (int i=0; i<T; ++i)
    {
        int n;
        cin >> n;
        vector<int> A, B;
        A.resize(n);
        B.resize(n);
        for (int j=0; j<n; ++j)
        {
            cin >> A[j];
        }

        for (int j=0; j<n; ++j)
        {
            cin >> B[j];
        }

        bool satisfy = false;
        for (int k=0; k<n; ++k)
        {
            for (auto & v : do_operation(A, n, 0, k))
            {
                if (equal(B.begin(), B.end(), v.begin()))
                {
                    satisfy = true;
                    break;
                }
            }
        }

        if (satisfy)
        {
            cout << "Yes" << endl;
        }
        else 
        {
            cout << "No" << endl;
        }
    }
    return 0;
}