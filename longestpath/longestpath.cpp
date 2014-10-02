#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

const int N = 100005;

bool found[N];
vector<int> v[N];
int dist;

int dfs(int node) {
  found[node] = true;

  int d1 = 0, d2 = 0;

  for (int i = 0; i < v[node].size(); i++) {
    if (!found[v[node][i]]) {
      int d = dfs(v[node][i]);

      if (d > d1) {
        d2 = d1;
        d1 = d;
      } else if (d > d2) {
        d2 = d;
      }
    }
  }

  dist = max(dist, d1 + d2 + 1);

  return d1 + 1;
}

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n;

    cin >> n;

    for (int i = 0; i < n; i++) {
      v[i].clear();
    }
    memset(found, 0, sizeof(found));

    for (int i = 1; i < n; i++) {
      int x, y;

      cin >> x >> y;

      v[x].push_back(y);
      v[y].push_back(x);
    }

    dist = 0;
    dfs(0);

    cout << dist << "\n";

  }

  return 0;
}

