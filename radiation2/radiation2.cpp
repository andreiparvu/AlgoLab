#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <iostream>
#include <CGAL/Point_2.h>
#include <CGAL/Unique_hash_map.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;
typedef Triangulation::Finite_faces_iterator Face_iterator;

int main() {
  int nr_tests;

  cin >> nr_tests;

  while (nr_tests--) {
    int mc, n;

    cin >> mc >> n;

    vector<P> pts(mc);
    for (int i = 0; i < mc; i++) {
      cin >> pts[i];
    }

    Triangulation t;
    t.insert(pts.begin(), pts.end());

    CGAL::Unique_hash_map<Triangulation::Face_handle, vector<P>> m;

    for (int i = 0; i < n; i++) {
      P c;
      cin >> c;
      Triangulation::Face_handle v = t.locate(c);

      if (!m.is_defined(v)) {
        m[v] = vector<P>();
      }
      m[v].push_back(c);
    }

    int rsp = 0;
    for (Face_iterator it = t.faces_begin(); it != t.faces_end(); it++) {
      int cnt = m[it].size();

      cout << cnt << "\n";
      for (int i = 0; i < 3; i++) {
        Triangulation::Face_handle f = it->neighbor(i);

        if (m.is_defined(f)) {
          for (auto p : m[f]) {
            if (t.side_of_oriented_circle(it, p)) {
              cnt++;
            }
          }
          cout << "--" << cnt << "\n";
        }
      }

      rsp = max(rsp, cnt);
    }

    cout << rsp << "\n";
  }

  return 0;
}

