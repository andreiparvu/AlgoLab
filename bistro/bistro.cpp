#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <iostream>
#include <CGAL/Point_2.h>
#include <CGAL/Cartesian.h>

using namespace std;

using namespace CGAL;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;

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

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
      K::Point_2 curp;

      cin >> curp;

      cout << (long)CGAL::to_double(CGAL::squared_distance(t.nearest_vertex(curp)->point(), curp)) << "\n";
    }
  }

  return 0;
}

