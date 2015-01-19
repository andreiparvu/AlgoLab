#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <CGAL/Point_2.h>
#include <CGAL/Segment_2.h>
#include <CGAL/Unique_hash_map.h>
#include <cstdio>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef Triangulation::Finite_edges_iterator Edge_iterator;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;

struct Contains {
  P p0, p1;

  Contains(const P &p, const P &q) : p0(p), p1(q) {}

  bool operator()(const P &p, const P &q) const {
    return CGAL::side_of_bounded_circle(p0, p1, p, q) == CGAL::ON_BOUNDED_SIDE;
  }
};

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

    for (Face_iterator it = t.finite_faces_begin();
        it != t.finite_faces_end(); it++) {
      m[it] = vector<P>();
    }

    for (int i = 0; i < n; i++) {
      P c;
      cin >> c;

      vector<Face_handle> vcur;

      t.get_conflicts(c, back_inserter(vcur));

      for (auto it : vcur) {
        m[it].push_back(c);
      }
    }

    for (Face_iterator it = t.finite_faces_begin();
        it != t.finite_faces_end(); it++) {
      sort(m[it].begin(), m[it].end());
    }

    int rsp = 0;
    for (Edge_iterator it = t.finite_edges_begin();
        it != t.finite_edges_end(); it++) {
      Face_handle f1 = it->first;
      Face_handle f2 = f1->neighbor(it->second);

      vector<P> set1, set2;

      set_difference(m[f1].begin(), m[f1].end(),
                     m[f2].begin(), m[f2].end(),
                     back_inserter(set1));
      set_difference(m[f2].begin(), m[f2].end(),
                     m[f1].begin(), m[f1].end(),
                     back_inserter(set2));

      S s = t.segment(it);
      Contains cont(s[0], s[1]);

      sort(set1.begin(), set1.end(), cont);
      sort(set2.begin(), set2.end(), cont);

      int cur = m[f1].size();

      auto pit1 = set1.begin();
      auto pit2 = set2.rbegin();

      for (;; pit2++) {
        rsp = max(rsp, cur);
        if (pit2 == set2.rend()) {
          break;
        }

        cur++;
        for (; pit1 != set1.end() && !cont(*pit2, *pit1); pit1++, cur--);
      }
    }

    cout << rsp << "\n";
  }

  return 0;
}

