#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
  int tests;

  cin >> tests;

  for (;tests--;) {
    int n;
    cin >> n;

    vector<int> m(n);

    for (int i = 0; i < n; i++) {
      cin >> m[i];
    }

    vector<pair<unsigned int, int> > v;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m[i]; j++) {
        unsigned int poz;

        cin >> poz;

        v.push_back(make_pair(poz, i));
      }
    }

    sort(v.begin(), v.end());

    vector<int> mp(n, 0);
    unsigned int rez = 2200000000;
    unsigned int start = 0;
    int cnt = 0;
    for (int i = 0; i < v.size(); i++) {
      if (mp[v[i].second] == 0) {
        cnt++;
      }
      mp[v[i].second]++;

      if (cnt == n) {
        for (; cnt == n; start++) {
          rez = min(rez, v[i].first - v[start].first + 1);

          mp[v[start].second]--;
          if (mp[v[start].second] == 0) {
            cnt--;
          }
        }
      }
    }

    cout << rez << "\n";
  }

  return 0;
}


