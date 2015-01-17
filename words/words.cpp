#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int MOD = 100003;

int d[105][11];

int sm(int i, int j) {
  if (j < 0) {
    return 0;
  }
  return d[i][j];
}

int main() {
  int nr_tests;

  cin >> nr_tests;

  while (nr_tests--) {
    int n, k;
    cin >> k >> n;

    memset(d, 0, sizeof(d));

    for (int i = 0; i <= k; i++) {
      d[1][i] = 1;
    }

    int rez = k + 1;
    for (int i = 2; i <= n; i++) {
      rez = 0;
      for (int j = 0; j <= k; j++) {
        d[i][j] = (sm(i - 1, j - 1) + sm(i - 1, j) +
          sm(i - 1, j + 1)) % MOD;
        rez += d[i][j];
        if (rez >= MOD) {
          rez -= MOD;
        }
      }
    }

    cout << rez << "\n";
  }

  return 0;
}


