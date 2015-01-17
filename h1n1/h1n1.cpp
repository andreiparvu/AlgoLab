#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <vector>
#include <iostream>
#include <CGAL/Point_2.h>
#include <map>
#include <queue>
#include <CGAL/Unique_hash_map.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef K::Point_2 P;
typedef Triangulation::Finite_faces_iterator Face_iterator;

inline void add(Face_iterator &it, int i1, int i2, int i3,
  CGAL::Unique_hash_map<Triangulation::Face_handle, vector<pair<Triangulation::Face_handle, long>>> &v) {

  long dist = CGAL::squared_distance(it->vertex(i1)->point(),
      it->vertex(i2)->point()) / 4;

  v[it].push_back(make_pair(it->neighbor(i3), dist));
  v[it->neighbor(i3)].push_back(make_pair(it, dist));
}

inline long my_min(long a, long b) {
  if (a == -1) {
    return b;
  }

  return a < b ? a : b;
}

bool dfs(Triangulation &t, Triangulation::Face_handle &p,
    CGAL::Unique_hash_map<Triangulation::Face_handle, vector<pair<Triangulation::Face_handle, long>>> &v,
    CGAL::Unique_hash_map<Triangulation::Face_handle, int> &fst,
    long d, int label) {
  fst[p] = label;

  if (t.is_infinite(p)) {
    return true;
  }

  for (auto next : v[p]) {
    if (fst[next.first] != label && next.second >= d) {
      bool b = dfs(t, next.first, v, fst, d, label);
      if (b) {
        return true;
      }
    }
  }

  return false;
}

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

    CGAL::Unique_hash_map<Triangulation::Face_handle, vector<pair<Triangulation::Face_handle, long>>> v;
    CGAL::Unique_hash_map<Triangulation::Face_handle, int> fst;

    for (Face_iterator it = t.faces_begin(); it != t.faces_end(); it++) {
      add(it, 0, 1, 2, v);
      add(it, 1, 2, 0, v);
      add(it, 2, 0, 1, v);
    }

    int m;
    cin >> m;

    for (int i = 0; i < m; i++) {
      K::Point_2 p;
      cin >> p;
      long d;
      cin >> d;

      Triangulation::Face_handle f = t.locate(p);
      long d4 = CGAL::squared_distance(t.nearest_vertex(p)->point(), p);

      if (d > d4) {
        cout << "n";
        continue;
      }

      if (t.is_infinite(f)) {
        cout << "y";
      } else {
        if (dfs(t, f, v, fst, d, i)) {
          cout << "y";
        } else {
          cout << "n";
        }
      }
    }
    cout << "\n";
  }

  return 0;
}

