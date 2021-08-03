#include <iostream>
#include <thread>

using namespace std;

thread_local int cnt = 0;
// static int cnt = 0;

int main() {
  std::thread t1([&]() {
    cnt++;
    cout << cnt << endl;
  });

  std::thread t2([&]() {
    cnt++;
    cout << cnt << endl;
  });

  t1.join();
  t2.join();
  return 0;
}