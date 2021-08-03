#include <iostream>
#include <vector>

using namespace std;

bool judge(const vector<int> &a, int v1, int v2) {
  return a[v1] == 0 && a[v2] == 0 && v1 != v2;
}

int main() {
  int T;
  cin >> T;

  for (int i = 0; i < T; ++i) {
    int n;
    cin >> n;

    vector<int> v;
    vector<int> a;
    vector<int> ncnt;
    v.resize(n);
    a.resize(100000);

    int min = 100000;

    for (int j = 0; j < n; ++j) {
      cin >> v[j];

      a[v[j]]++;

      if (min > v[j]) {
        min = v[j]; // find minuim
      }
    }

    // cout << "min: " << min << endl;

    // cout << a[5] << " " << a[6] << " " << a[7] << " " << a[8] << endl;
    int difftotal = 0;
    int diffval = 0;

    for (int j = 0; j < a.size(); ++j) {
      if (a[j] != 0) {
        difftotal++;
        if (a[j] > 1) {
          diffval = j;
        }
      }
    }

    int cnt = 0;
    if (abs(difftotal - n) == 1) { // 只有一项重复, 结果乘以 2
      for (int k = 1; k <= diffval / 2; ++k) {
        /*
      if (k >= min || diffval - k >= min) {
        continue;
      }
      */
        if (judge(a, k, diffval - k)) {
          // cout << v[j] << " " << k << " " << v[j] - k << endl;
          cnt++;
          break;
        }
      }
      cnt *= 2;
    } else if (abs(difftotal - n) >= 2) { // 至少有两项重复, 不成立
      cnt = 0;
    } else { // 完全不重复的, 直接遍历
      for (int j = 0; j < n; ++j) {
        for (int k = 1; k <= v[j] / 2; ++k) {
          /*
        if (k >= min || v[j] - k >= min) {
          continue;
        }
        */
          if (judge(a, k, v[j] - k)) {
            // cout << v[j] << " " << k << " " << v[j] - k << endl;
            cnt++;
            break;
          }
        }
      }
    }

    cout << cnt << endl;
  }

  return 0;
}
