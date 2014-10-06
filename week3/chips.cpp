#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdlib>

using namespace std;

int color[5][50000];

vector<int> nr(5);

inline int comp(int v) {
  if (v <= 1) {
    return 0;
  }

  return 1 << (v - 2);
}

typedef long long lint;

lint *****d;

lint doit(vector<int> v) {
  if (!v[0] && !v[1] && !v[2] && !v[3] && !v[4]) {
    d[0][0][0][0][0] = 0;
    return 0;
  }

  if (d[v[0]][v[1]][v[2]][v[3]][v[4]] == -1) {
    vector<pair<int, int> > cur;

    for (int t = 0; t < 5; t++) {
      if (v[t] > 0) {
        cur.push_back(make_pair(color[t][v[t] - 1], t));
      }
    }

    sort(cur.begin(), cur.end());

    int j = 0;
    for (int i = 0; i < cur.size(); i++) {
      for (; j < cur.size() && cur[j].first == cur[i].first; j++);

      int l = j - i;
      for (int t = 1; t < (1 << (l + 1)); t++) {
        vector<int> w = v;
        int cnt = 0;
        for (int k = 0; k < l; k++) {
          if ((t & (1 << k)) > 0) {
            w[cur[i + k].second]--;
            cnt++;
          }
        }

        d[v[0]][v[1]][v[2]][v[3]][v[4]] = max(d[v[0]][v[1]][v[2]][v[3]][v[4]],
          doit(w) + (lint)comp(cnt));
      }
    }
  }

  return d[v[0]][v[1]][v[2]][v[3]][v[4]];
}

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n;
    cin >> n;

    for (int i = 0; i < 5; i++) {
      nr[i] = 1;
    }

    vector<int> nr2(5, 0);
    for (int i = 0; i < n; i++) {
      cin >> nr[i];
      nr2[i] = nr[i];
      nr[i]++;
    }

    d = (lint*****)malloc(nr[0] * sizeof(lint****));
    for (int i = 0; i < nr[0]; i++) {
      d[i] = (lint****)malloc(nr[1] * sizeof(lint***));
      for (int j = 0; j < nr[1]; j++) {
        d[i][j] = (lint***)malloc(nr[2] * sizeof(lint**));
        for (int k = 0; k < nr[2]; k++) {
          d[i][j][k] = (lint**)malloc(nr[3] * sizeof(lint*));
          for (int l = 0; l < nr[3]; l++) {
            d[i][j][k][l] = (lint*)malloc(nr[4] * sizeof(lint));
            for (int t = 0; t < nr[4]; t++) {
              d[i][j][k][l][t] = -1;
            }
          }
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < nr2[i]; j++) {
        cin >> color[i][j];
      }
    }

    cout << doit(nr2) << "\n";
  }

  return 0;
}

