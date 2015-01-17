#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <stdexcept>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef K::Point_2 P;
typedef K::Line_2 Line;

inline bool do_check(pair<P, P> &p1, P &pp) {
  return (CGAL::left_turn(p1.first, p1.second, pp) ||
          CGAL::collinear(p1.first, p1.second, pp));
}

inline bool check_point(vector<pair<P, P>> &pl, P &pp) {
  return do_check(pl[0], pp) && do_check(pl[1], pp) && do_check(pl[2], pp);
}

void build(P &p0, P &p1, P &p2, pair<P, P> &lines) {
  if (CGAL::left_turn(p0, p1, p2)) {
    lines = make_pair(p0, p1);
  } else {
    lines = make_pair(p1, p0);
  }
}

int main() {
  ios_base::sync_with_stdio(false);

  int nrTests;

  cin >> nrTests;

  while (nrTests--) {
    int n, m;

    cin >> m >> n;

    vector<P> paths(m);
    for (int i = 0; i < m; i++) {
      cin >> paths[i];
    }

    vector<vector<int>> good(n, vector<int>());
    vector<vector<pair<P, P>>>
      lines(n, vector<pair<P, P>>(3));

    for (int i = 0; i < n; i++) {
      P p0, p1, p2, p3, p4, p5;

      cin >> p0 >> p1 >> p2 >> p3 >> p4 >> p5;


      build(p0, p1, p2, lines[i][0]);
      build(p2, p3, p4, lines[i][1]);
      build(p4, p5, p0, lines[i][2]);
    }

    int rez = n;

    vector<int> curPaths(m - 1, 0);
    int end = 0;
    int size = 0;
    for (int i = 0; i < n; i++) {
      for (; end < n && size < m - 1; end++) {
        for (int k = 0; k < m - 1; k++) {
          if (check_point(lines[end], paths[k]) &&
              check_point(lines[end], paths[k + 1])) {
            good[end].push_back(k);

            if (curPaths[k] == 0) {
              size++;
            }
            curPaths[k]++;
          }
        }
      }

      if (size == m - 1) {
        rez = min(rez, end - i);
        if (rez == 1) {
          break;
        }
        for (int k = 0; k < good[i].size(); k++) {
          curPaths[good[i][k]]--;
          if (curPaths[good[i][k]] == 0) {
            size--;
          }
        }
      }
    }

    cout << rez << "\n";
  }

  return 0;
}

