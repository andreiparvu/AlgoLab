#include <vector>
#include <cstdio>

using namespace std;


int main() {
  int tests;

  scanf("%d", &tests);
  while (tests--) {
    int n, m;
    int r, b;

    scanf("%d%d", &n, &m);
    scanf("%d%d", &r, &b);

    vector<vector<int> > out(n + 1, vector<int>());

    for (int i = 0; i < m; i++) {
      int x, y;
      scanf("%d%d", &x, &y);

      out[x].push_back(y);
    }

    vector<vector<int> > d(n + 1, vector<int>(2, 0));

    d[n][0] = d[n][1] = 0;

    for (int i = n - 1; i > 0; i--) {
      int d1 = 0, d0 = 0x3f3f3f3f;
      for (int j = 0; j < out[i].size(); j++) {
        d1 = max(d1, d[out[i][j]][0] + 1);
        d0 = min(d0, d[out[i][j]][1] + 1);
      }

      d[i][0] = d0;
      d[i][1] = d1;
    }

    if (d[b][0] == d[r][0]) {
      if (d[b][0] % 2 == 1) {
        printf("0\n");
      } else {
        printf("1\n");
      }
    } else if (d[r][0] < d[b][0]) {
      printf("0\n");
    } else {
      printf("1\n");
    }
  }

  return 0;
}


