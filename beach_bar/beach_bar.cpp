#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

set<int> sol;
vector<int> v;
int main() {
  int nr_tests;

  cin >> nr_tests;

  while (nr_tests--) {
    int n;
    cin >> n;

    v.clear();
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      v.push_back(x);
    }

    sort(v.begin(), v.end());

    int rsp = 0, rd = -1, poz = 0;
    for (int i = 0; i < v.size(); i++) {
      for (; v[poz] - v[i] <= 200 && poz < v.size(); poz++);

      int mid = (v[poz - 1] + v[i]);
      int dist = max(mid / 2 - v[i], v[poz - 1] - mid / 2);
//      fprintf(stderr, "%d %d - %d %d\n", poz - 1, poz - i, mid, dist);
      if (poz - i > rsp || (poz - i == rsp && dist < rd)) {
        rsp = poz - i;
        rd = dist;
        sol.clear();
        sol.insert(mid / 2);
        if (mid % 2 == 1) {
          sol.insert(mid / 2 + 1);
        } else if (mid % 2 == -1) {
          sol.insert(mid / 2 - 1);
        }
      } else if (poz - i == rsp && dist == rd) {
        sol.insert(mid / 2);
        if (mid % 2 == 1) {
          sol.insert(mid / 2 + 1);
        } else if (mid % 2 == -1) {
          sol.insert(mid / 2 - 1);
        }
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
