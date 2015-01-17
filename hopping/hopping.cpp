#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int nr_tests;

  ios_base::sync_with_stdio(false);
  cin >> nr_tests;

  while (nr_tests--) {
    int k, r, e;

    cin >> k >> r >> e;

    vector<int> def(k + 1);
    for (int i = 1; i < k; i++) {
      cin >> def[i];
    }

    vector<pair<int, int> > d(k + 1, make_pair(-1, 0));
    d[0] = make_pair(e, 0);

    for (int i = 0; i < k; i++) {
      for (int j = i + 1; j <= i + r && j <= k; j++) {
        int nw = d[i].first - def[j];
        if (nw > d[j].first) {
          d[j] = make_pair(nw, d[i].second + 1);
        } else if (nw == d[j].first) {
          d[j].second = min(d[j].second, d[i].second + 1);
        }
      }
    }

    if (d[k].first <= 0) {
      cout << "safe\n";
    } else {
      cout << d[k].second - 1 << " " << d[k].first << "\n";
    }

  }

  return 0;
}

