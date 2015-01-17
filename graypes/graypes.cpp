#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <iostream>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_vertices_iterator vert_it;

int main() {
  ios_base::sync_with_stdio(false);

  for (;;) {
    int n;
    cin >> n;

    if (!n) {
      break;
    }

    vector<K::Point_2> pts(n);
    for (int i = 0; i < n; i++) {
      cin >> pts[i];
    }

    Triangulation t;
    t.insert(pts.begin(), pts.end());

    K::FT rez = -1;
    for (vert_it it = t.finite_vertices_begin(); it!= t.finite_vertices_end(); it++) {
      Triangulation::Vertex_circulator circulator = t.incident_vertices(it->handle()),
        done(circulator);

      do  {
        if (!t.is_infinite(circulator)) {
          if (CGAL::squared_distance(it->point(), circulator->point()) < rez || rez == -1) {
            rez = CGAL::squared_distance(it->point(), circulator->point());
          }
        }
      } while (++circulator != done);
    }

    cout << ceil(sqrt(rez) * 50) << "\n";
  }

  return 0;
}

