#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#include <cstring>

vector<int> in[500005];
int out[500005];

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n, m;
    cin >> n >> m;

    memset(out, 0, sizeof(out));

    for (int i = 1; i <= m; i++) {
      in[i].clear();
    }

    int sol = n;
    for (int i = 0; i < n; i++) {
      int p, q;
      cin >> p >> q;

      if (p == 0 && q == 0) {
        sol--;
      } else {
        in[p].push_back(q);
        out[q]++;
      }
    }

    int inq = 0;
    int mx = 0;
    for (int i = 1; i <= m; i++) {
      sort(in[i].begin(), in[i].end(), greater<int>());
      bool here = false, didit = false;
      for (int j = 0; j < in[i].size(); j++) {
        if (in[i][j] <= mx) {
          sol--;
          if (in[i][j] == mx && here && !didit) {
            sol--;
            didit = true;
          }
        } else {
          mx = max(mx, in[i][j]);
          here = true;
        }
      }
      inq += in[i].size();

      if (inq == 0) {
        sol = 0;
        break;
      }

      inq -= out[i];
    }

    cout << sol << "\n";
  }

  return 0;
}

