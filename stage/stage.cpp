#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <iostream>
#include <CGAL/Point_2.h>
#include <map>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;

int main() {
  std::ios::sync_with_stdio(false);
  int nr_tests;

  cin >> nr_tests;

  while (nr_tests--) {
    int n, m;
    cin >> n >> m;

    vector<pair<P, K::FT> > part(n);
    map<P, int> vert;
    for (int i = 0; i < n; i++) {
      cin >> part[i].first >> part[i].second;
    }

    K::FT lr;
    vector<P> pts(m);

    cin >> lr;
    for (int i = 0; i < m; i++) {
      cin >> pts[i];

      vert[pts[i]] = i;
    }

    Triangulation t;
    t.insert(pts.begin(), pts.end());

    int mx = 0;
    vector<int> sol;
    for (int i = 0; i < n; i++) {
      Triangulation::Vertex_handle v = t.nearest_vertex(part[i].first);
      P cur = v->point();

      mx = max(vert[cur], mx);
      if (CGAL::squared_distance(cur, part[i].first) >= (lr + part[i].second) *
          (lr + part[i].second)) {
        sol.push_back(i);
      }
    }

    int last = m - 1;
    while (sol.size() == 0) {
      for (int j = last; j >= mx; j--) {
        t.remove(t.nearest_vertex(pts[j]));
      }
      last = mx - 1;

      mx = 0;
      for (int i = 0; i < n; i++) {
        Triangulation::Vertex_handle v = t.nearest_vertex(part[i].first);
        P cur = v->point();

        mx = max(vert[cur], mx);
        if (CGAL::squared_distance(cur, part[i].first) >= (lr + part[i].second) *
            (lr + part[i].second)) {
          sol.push_back(i);
        }
      }
    }

    for (int i = 0; i < sol.size(); i++) {
      cout << sol[i] << " ";
    }
    cout << "\n";
  }

  return 0;
}

