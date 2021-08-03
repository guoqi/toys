#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int T;
  cin >> T;

  for (int i = 0; i < T; ++i) {
    int n, d;
    cin >> n >> d;

    vector<int> v;
    v.resize(n);

    for (int j = 0; j < n; ++j) {
      cin >> v[j];
    }

    std::sort(v.begin(), v.end());

    double time = 0;
    for (int j = 0; j < n; ++j) {
    }
  }

  return 0;
}