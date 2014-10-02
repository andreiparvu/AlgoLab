#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int d[1000005][2];
int v[1000005];

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n, k, x;

    cin >> n >> k >> x;

    vector<int> pattern(k + 1, 0);

    for (int i = 0; i < k; i++) {
      if ((x & (1 << i)) > 0) {
        pattern[k - i - 1] = 1;
      }
    }

    for (int i = 0; i < n; i++) {
      cin >> v[i];
    }

    memset(d, 0x3f, sizeof(d));

    d[n][0] = 0;
    for (int i = n - 1, j = k - 1; i >= 0; i--, j--) {
      bool b = (v[i] == pattern[j]);

      if (j == k - 1) {
        if (b == true) {
          d[i][0] = min(d[i + 1][0], d[i + 1][1] + 1);
          d[i][1] = min(d[i + 1][1] + 1, d[i + 1][0] + 2);
        } else {
          d[i][0] = min(d[i + 1][0] + 1, d[i + 1][1] + 1);
          d[i][1] = min(d[i + 1][1], d[i + 1][0] + 1);
        }
      } else {
        if (b == true) {
          d[i][0] = d[i + 1][0];
          d[i][1] = d[i + 1][1] + 1;
        } else {
          d[i][0] = d[i + 1][0] + 1;
          d[i][1] = d[i + 1][1];
        }
      }

      if (j == 0) {
        j = k;
      }
    }

    cout << min(d[0][0], d[0][1]) << "\n";
  }

  return 0;
}

