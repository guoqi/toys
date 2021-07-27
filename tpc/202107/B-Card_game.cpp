#include <iostream>
#include <vector>

using namespace std;

bool fetch_card(int k, int m, vector<vector<int>> &vv) {
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < k; ++j) {
      if (i == j) {
        continue;
      }
      if (vv[i].size() > m && vv[j].size() > m && vv[i][m] == vv[j][m]) {
        return true;
      }
    }
  }
  return false;
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    int n, k;
    cin >> n >> k;
    vector<int> m;
    m.resize(k);
    vector<vector<int>> vv;
    vv.resize(k);
    for (int j = 0; j < k; ++j) {
      cin >> m[j];
      vv[j].resize(m[j]);
      for (int q = 0; q < m[j]; ++q) {
        cin >> vv[j][q];
      }
    }

    int turns = 1;
  }
  return 0;
}
