#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int N = 105;
const int inf = 0x3f3f3f3f;

vector<vector<int> > norm(N, vector<int>()), inv(N, vector<int>());

void bfs(int start, vector<vector<int> > &v, vector<int> &d) {
  queue<int> q;
  q.push(start);
  d[start] = 0;

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int i = 0; i < v[cur].size(); i++) {
      if (d[v[cur][i]] == inf) {
        d[v[cur][i]] = d[cur] + 1;
        q.push(v[cur][i]);
      }
    }
  }
}

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n, m, start, finish;

    cin >> n >> m;
    cin >> start >> finish;

    for (int i = 1; i <= n; i++) {
      norm[i].clear();
      inv[i].clear();
    }

    for (int i = 0; i < m; i++) {
      int x, y;

      cin >> x >> y;

      norm[x].push_back(y);
      inv[y].push_back(x);

    }

    vector<int> dist(n + 1, inf), dist_inv(n + 1, inf);

    bfs(start, norm, dist);
    bfs(finish, inv, dist_inv);

    int shortest = dist[finish], nrs = 0;
    int rsp = inf;

    for (int i = 1; i <= n; i++) {
      for (int j = 0; j < norm[i].size(); j++) {
        if (dist[i] + 1 + dist_inv[norm[i][j]] == shortest) {
          nrs++;
        }

        if (dist[i] + 1 + dist_inv[norm[i][j]] > shortest) {
          rsp = min(rsp, dist[i] + 1 + dist_inv[norm[i][j]]);
        }
      }
    }

    if (nrs > shortest) {
      cout << shortest << "\n";
    } else if (rsp == inf) {
      cout << "no\n";
    } else {
      cout << rsp << "\n";
    }
  }

  return 0;
}

