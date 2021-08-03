#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int T;
  cin >> T;

  for (int i = 0; i < T; ++i) {
    int n, k;
    cin >> n >> k;
    vector<int> va, vb;
    va.resize(n);
    vb.resize(n);
    for (int j = 0; j < n; ++j) {
      cin >> va[j];
    }
    for (int j = 0; j < n; ++j) {
      cin >> vb[j];
    }

    va[0] = va[0] + vb[0];
    int tencent = va[0];
    sort(va.begin(), va.end(), [](int a, int b) { return a > b; });

    bool find = false;
    for (int j = 0; j < n; ++j) {
      if (va[j] == tencent && k >= j + 1) {
        find = true;
        break;
      }
    }

    if (find) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }

  return 0;
}
