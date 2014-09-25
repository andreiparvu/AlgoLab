#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n;

    cin >> n;

    vector<pair<int, int> > v;

    for (int i = 0; i < n; i++) {
      int x, y;

      cin >> x >> y;

      v.push_back(make_pair(y, x));
    }

    sort(v.begin(), v.end());

    vector<int> d(1000000, 0);

    d[v[0].first] = 1;
    int rez = 1;
    for (int i = 1; i < n; i++) {
      for (int j = 0; j < v[i].first - v[i].second; j++) {
        d[v[i].first] = max(d[v[i].first], d[j] + 1);
        rez = max(rez, d[v[i].first]);
      }

      for (int j = v[i].first - v[i].second; j <= v[i].first; j++) {
        d[j + v[i].second] = max(d[j + v[i].second], d[j] + 1);

        rez = max(rez, d[j] + 1);
      }
    }

    cout << rez << "\n";
  }

  return 0;
}

