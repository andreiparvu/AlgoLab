#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

const int N = 1002;

int d[N][N];

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n;

    cin >> n;

    int s;
    if (n % 2 == 1) {
      s = 1;
    } else {
      s = 0;
    }

    vector<int> values(n + 1), sum(n + 1, 0);

    for (int i = 1; i <= n; i++) {
      int x;
      cin >> x;
      values[i] = x;
      sum[i] = sum[i - 1] + x;

      d[i][i] = x * s;
    }

    s = 1 - s;
    for (int k = 1; k < n; k++, s = 1 - s) {
      for (int i = 1; i + k <= n; i++) {
        int j = i + k;

        if (s) {
          d[i][j] = max(d[i + 1][j] + values[i], d[i][j - 1] + values[j]);
        } else {
          int allsum1 = sum[j] - sum[i],
              allsum2 = sum[j - 1] - sum[i - 1];

          int mysum1 = allsum1 - d[i + 1][j] + values[i],
              mysum2 = allsum2 - d[i][j - 1] + values[j];

          if (mysum1 > mysum2) {
            d[i][j] = d[i + 1][j];
          } else {
            d[i][j] = d[i][j - 1];
          }
        }
      }
    }

    cout << d[1][n] << "\n";
  }

  return 0;
}

