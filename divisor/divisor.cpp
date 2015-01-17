#include <cstdio>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int getdiv(int p1) {
  int p = 1;
  for (int j = 2; j * j <= p1; j++) {
    if (p1 % j == 0) {
      p = p1 / j;
      break;
    }
  }

  return p;
}

int main() {
  int nr_tests;

  cin >> nr_tests;

  int ind = 0;
  vector<int> dist(10000001), mark(10000001);

  while (nr_tests--) {
    int n, c;

    cin >> n >> c;

#if 0
    vector<vector<int>> v(n + 1, vector<int>());

    for (int i = 1; i <= n; i++) {
      int p = 1;
      for (int j = 2; j * j <= i; j++) {
        if (i % j == 0) {
          p = i / j;
          break;
        }
      }

      v[p].push_back(i);
      v[i].push_back(p);
    }
#endif

    for (int i = 1; i <= c; i++) {
      int p1, p2;

      cin >> p1 >> p2;

      if (p1 == p2) {
        cout << "0\n";
        continue;
      }

#if 0
      queue<int> q;
      vector<int> fst(n + 1, -1);

      q.push(p1);
      fst[p1] = 0;

      bool done = false;
      while (!q.empty() && !done) {
        int cur = q.front();
        q.pop();

        for (auto next : v[cur]) {
          if (fst[next] == -1) {
            fst[next] = fst[cur] + 1;
            q.push(next);

            if (next == p2) {
              cout << fst[next] << "\n";
              done = true;
              break;
            }
          }
        }
      }
#endif
      dist[p1] = 0;
      dist[p2] = 0;
      mark[p1] = ++ind;

      int p;
      while (p1 > 1) {
        p = getdiv(p1);
        dist[p] = dist[p1] + 1;
        mark[p] = ind;

        p1 = p;

      }

      if (mark[p2] == ind) {
        cout << dist[p2] << "\n";
        continue;
      }

      mark[p2] = ind;
      while (p2 > 1) {
        p = getdiv(p2);
        if (mark[p] == ind) {
          cout << dist[p] + dist[p2] + 1 << "\n";
          break;
        }
        dist[p] = dist[p2] + 1;
        mark[p] = ind;

        p2 = p;
      }
    }
  }

  return 0;
}


