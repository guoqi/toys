#include <endian.h>
#include <iostream>
#include <vector>

using namespace std;

int winner(vector<int> &a, int j) {
  if (j >= a.size()) {
    return a[j % a.size()];
  }
  return a[j];
}

bool all_same(vector<int> &a) {
  int start = a[0];
  for (int i = 0; i < a.size(); ++i) {
    if (start != a[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    int n;
    long long k;
    cin >> n >> k;
    vector<int> a;
    a.resize(n);
    for (int j = 0; j < n; ++j) {
      cin >> a[j];
    }

    int total = 1;
    int start = a[0];
    int win = start;
    int max_total = 0;
    long long j = 1;
    if (!all_same(a)) {
      while (j < 2 * n + 1) {
        if (total == k) {
          break;
        }

        win = winner(a, j);
        if (start == win) {
          total++;
        } else {
          total = 1;
          start = win;
        }
        ++j;

        if (max_total < total) {
          max_total = total;
        }
      }
    } else {
      total = k;
      j = k;
      win = start;
    }

    if (total == k) {
      cout << j << " " << win << endl;
    } else {
      cout << "INF" << endl;
    }
  }

  return 0;
}