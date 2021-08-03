#include <iostream>
#include <vector>

using namespace std;

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {

    int n;
    cin >> n;

    int negnum = 0;
    int posnum = 0;
    int zero = 0;
    for (int j = 0; j < n; ++j) {
      int tmp;
      cin >> tmp;
      if (tmp > 0) {
        posnum++;
      } else if (tmp < 0) {
        negnum++;
      } else {
        zero++;
      }
    }

    for (int k = 0; k < zero; ++k) {
      if (posnum > negnum) {
        posnum--;
      } else {
        negnum--;
      }
    }

    if (posnum < 0 || negnum < 0) {
      cout << "Yes" << endl;
    } else {
      if (abs(posnum - negnum) <= 1) {
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
    }
  }
  return 0;
}