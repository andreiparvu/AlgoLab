#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

const int N = 100005;
const int INF = 0x3f3f3f3f;

int d[N][2][2];
bool fst[N][2][2];

vector<vector<pair<int, int> > > v(N, vector<pair<int, int> >());

int main() {
  int tests;

  scanf("%d", &tests);

  while (tests--) {
    int n, m;
    int s, t;

    scanf("%d %d", &n, &m);
    scanf("%d %d", &s, &t);

    for (int i = 0; i < m; i++) {
      int x, y, c;

      scanf("%d%d%d", &x, &y, &c);

      v[x].push_back(make_pair(y, c));
    }

    memset(d, 0x3f, sizeof(d));
    memset(fst, 0, sizeof(fst));

    d[s][0][0] = 0;

    queue<pair<int, pair<int, int> > > q;

    q.push(make_pair(s, make_pair(0, 0)));
    fst[s][0][0] = true;

    while (!q.empty()) {
      pair<int, pair<int, int> > cur = q.front();
      q.pop();

      int node = cur.first;
      int r = cur.second.first, c = cur.second.second;
      fst[node][r][c] = false;

      for (int i = 0; i < (int)v[node].size(); i++) {
        int cmod = v[node][i].second % 2;
        int next;

        if (!cmod) {
          next = c;
        } else {
          next = 1 - c;
        }

        if (d[node][r][c] + v[node][i].second < d[v[node][i].first][1 - r][next]) {
          d[v[node][i].first][1 - r][next] = d[node][r][c] + v[node][i].second;

          if (!fst[v[node][i].first][1 - r][next]) {
            fst[v[node][i].first][1 - r][next] = true;
            q.push(make_pair(v[node][i].first, make_pair(1 - r, next)));
          }
        }
      }
    }

    int rez = d[t][1][1];

    if (rez == INF) {
      printf("no\n");
    } else {
      printf("%d\n", rez);
    }

    for (int i = 0; i < n; i++) {
      v[i].clear();
    }
  }

  return 0;
}

