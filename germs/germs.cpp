#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <iostream>
#include <CGAL/Point_2.h>
#include <map>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_vertices_iterator vert_it;
typedef K::Point_2 P;

long getTime(K::FT distance) {
  return ceil(sqrt(distance - 0.5));
}

int main() {
  ios_base::sync_with_stdio(false);

  for (;;) {
    int n;
    cin >> n;

    if (!n) {
      break;
    }

    long l, b, r, p;
    cin >> l >> r >> b >> p;

    K::Segment_2 S1(P(l, r), P(b, r)), S2(P(l, p), P(b, p)),
      S3(P(l, r), P(l, p)), S4(P(b, r), P(b, p));

    map<K::Point_2, long> rez;

    vector<K::Point_2> pts(n);
    for (int i = 0; i < n; i++) {
      cin >> pts[i];

      rez[pts[i]] = min(min(getTime(sqrt(CGAL::squared_distance(pts[i], S1))),
                       getTime(sqrt(CGAL::squared_distance(pts[i], S2)))),
                   min(getTime(sqrt(CGAL::squared_distance(pts[i], S3))),
                       getTime(sqrt(CGAL::squared_distance(pts[i], S4))))
               );
    }

    Triangulation t;
    t.insert(pts.begin(), pts.end());

    for (vert_it it = t.finite_vertices_begin(); it != t.finite_vertices_end(); it++) {
      Triangulation::Vertex_circulator circulator = t.incident_vertices(it->handle()),
        done(circulator);

      if (circulator != NULL) {
        do {
          if (!t.is_infinite(circulator)) {
            rez[it->point()] = min(rez[it->point()],
                getTime(sqrt(CGAL::squared_distance(it->point(),
                      circulator->point())) / 2));
          }
        } while (++circulator != done);
      }
    }

    long r1 = -1, r2 = -1;

    vector<long> v;
    for (auto it : rez) {
      v.push_back(it.second);
    }

    sort(v.begin(), v.end());

    cout << v[0] << " " << v[n / 2] << " " << v[n - 1] << "\n";
  }

  return 0;
}

