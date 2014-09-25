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

    int end = v[0].first, ind = 0;
    int nrb = 1;
    for (int i = 1; i < v.size(); i++) {
      if (end <= v[i].first) {
      //  cout << v[i].first << "\n";
        nrb++;
        end = max(end, v[i].first - v[i].second) + v[i].second;
        ind = i;
      } else {
        int start = max(v[i].first - v[i].second, end - v[ind].second);

        if (start + v[i].second < end) {
        //  cout << v[ind].first << "-" << v[i].first << "\n";
          end = start + v[i].second;
          ind = i;
        }
      }
    }

    cout << nrb << "\n";
  }

  return 0;
}

