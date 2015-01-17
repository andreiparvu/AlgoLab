#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

set<int> sol;
int main() {
  int nr_tests;

  cin >> nr_tests;

  while (nr_tests--) {
    int n;
    cin >> n;

    vector<int> v(5000000, 0);
    int p1 = 5000000, p2 = 0;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;

      x += 2000000;
      v[x] = 1;

      p1 = min(p1, x);
      p2 = max(p2, x);
    }

    int rsp = 0, rd = -1, poz = 0;
    for (int i = p1; i <= p2; i++) {
      int cnt = 0;
      int d = 0;
      for (int k = i - 100; k <= i + 100; k++) {
        if (v[k]) {
          cnt++;
          d = max(d, i - k);
          d = max(d, k - i);
        }
      }

      if (cnt > rsp || (cnt == rsp && d < rd)) {
        rsp = cnt;
        rd = d;
        sol.clear();
        sol.insert(i - 2000000);
      } else if (cnt == rsp && d == rd) {
        sol.insert(i - 2000000);
      }
    }


    cout << rsp << " " << rd << "\n";
    int s = 0;
    for (auto i : sol) {
      if (s) {
        cout << " ";
      }
      s = 1;
      cout << i;
    }
    cout << "\n";
  }

  return 0;
}
