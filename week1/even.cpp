#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

const int N = 205;

int even[N][N][N], odd[N][N][N];
int main() {
  int tests;
  cin >> tests;

  while (tests--) {
    int n;
    cin >> n;

    vector<vector<int> > sum(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        int x;
        cin >> x;

        sum[i][j] = x + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
      }
    }


    memset(even, 0, sizeof(even));
    memset(odd, 0, sizeof(odd));

    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        even[0][i][j] = 1;
      }
    }

    for (int i = 1; i <= n; i++) {
      for (int l = 0; l <= n; l++) {
        for (int j = 0; j <= l; j++) {
          int s = sum[i][l] - sum[i][j];

          if (s % 2 == 0) {
            even[i][l][j] = even[i - 1][l][j] + 1;
            odd[i][l][j] = odd[i - 1][l][j];
          } else {
            odd[i][l][j] = odd[i - 1][l][j] + 1;
            even[i][l][j] = even[i - 1][l][j];
          }
        }
      }
    }

    int sol = 0;
    //cout << odd[1][1][0] << "\n";
    //for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      for (int k = 1; k <= n; k++) {
        for (int l = j; l <= n; l++) {
          int s = (sum[k][l] - sum[k][j - 1]) % 2;

          if (s % 2 == 0) {
            sol += even[k - 1][l][j - 1];

            //printf("%d %d %d  %d\n", k, l, j, even[k - 1][l][j - 1]);
          } else {
            sol += odd[k - 1][l][j - 1];

            //printf("%d %d %d  %d\n", k, l, j, odd[k - 1][l][j - 1]);
          }
          /*if ((sum[k][l] - sum[i - 1][l] - sum[k][j - 1] + sum[i - 1][j - 1])
            % 2 == 0) {
            sol++;
            }*/
        }
      }
    }
    //}

    cout << sol << "\n";
  }

  return 0;
}

