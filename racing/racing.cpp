#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

#define ii pair<int, int>

int marked[35][35][10][10];
int frees[35][35];

inline int abs(int a) {
  return a < 0 ? -a : a;
}

queue<pair<ii, ii> > q;
int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n, m, x1, y1, x2, y2, p;

    cin >> m >> n;

    cin >> y1 >> x1 >> y2 >> x2;

    cin >> p;

    memset(frees, 0, sizeof(frees));

    for (int i = 0; i < p; i++) {
      int x1, y1, x2, y2;
      cin >> y1 >> x1 >> y2 >> x2;

      for (int j = x1; j <= x2; j++) {
        for (int k = y1; k <= y2; k++) {
          frees[j][k] = 1;
        }
      }
    }

    if (x1 == x2 && y1 == y2) {
      cout << "Optimal solution takes 0 hops.\n";
      continue;
    }

    memset(marked, 0, sizeof(marked));
    marked[x1][y1][3][3] = 1;

    q.push(make_pair(make_pair(x1, y1), make_pair(0, 0)));

    bool found = false;

    while (!q.empty()) {
      pair<ii, ii> cur = q.front();
      q.pop();

      for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
          int vx = cur.second.first + i,
              vy = cur.second.second + j;

          if (abs(vx) <= 3 && abs(vy) <= 3) {
            int newx = cur.first.first + vx,
                newy = cur.first.second + vy;

            if (0 <= newx && newx < n && newy >= 0 && newy < m &&
                frees[newx][newy] == 0) {
              if (!marked[newx][newy][vx + 3][vy + 3]) {
                marked[newx][newy][vx + 3][vy + 3] =
                  marked[cur.first.first][cur.first.second]
                              [cur.second.first + 3][cur.second.second + 3] + 1;

                if (newx == x2 && newy == y2 && !found) {
                  int res = marked[newx][newy][vx + 3][vy + 3] - 1;
                  cout << "Optimal solution takes " << res << " hops.\n";
                  found = true;
                }
                q.push(make_pair(make_pair(newx, newy), make_pair(vx, vy)));
              }
            }
          }
        }
      }
    }
    if (!found) {
      cout << "No solution.\n";
    }
  }

  return 0;
}
