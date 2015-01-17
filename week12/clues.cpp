#include <CGAL/basic.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <map>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Finite_vertices_iterator vert_it;

typedef K::Point_2 P;

bool dfs(int node, vector<int> &col, int c, vector<vector<int>  > &v,
    vector<int> &comp) {
  col[node] = c;

  bool ret = false;
  for (int i = 0; i < v[node].size(); i++) {
    int next = v[node][i];
    if (col[next] == -1) {
      comp[next] = comp[node];
      ret = ret || dfs(next, col, 1 - c, v, comp);
    } else if (col[next] == col[node]) {
      return true;
    }
  }

  return ret;
}

int find_min(vector<P> &s, P &start, long long r) {
  long long ret = -1;
  int p = -1;
  for (int i = 0; i < s.size(); i++) {
    long long d = CGAL::squared_distance(s[i], start);

    if (ret == -1 || d < ret) {
      ret = d;
      p = i;
    }
  }

  if (ret > r) {
    return -1;
  }

  return p;
}

int main() {
  ios_base::sync_with_stdio(false);
  int nr_tests;
  cin >> nr_tests;

  while (nr_tests--) {
    int n, m;
    long long r;

    cin >> n >> m >> r;
    r *= r;

    vector<P> s(n);
    map<P, int> mp;
    for (int i = 0; i < n; i++) {
      cin >> s[i];

      mp[s[i]] = i;
    }

    Triangulation t;
    t.insert(s.begin(), s.end());

    vector<vector<int> > v(n, vector<int>());

    for (vert_it it = t.finite_vertices_begin(); it!= t.finite_vertices_end(); it++) {
      Triangulation::Vertex_circulator circulator = t.incident_vertices(it->handle()),
        done(circulator);

      do  {
        if (!t.is_infinite(circulator)) {
          if (CGAL::squared_distance(it->point(), circulator->point()) <= r) {
            v[mp[it->point()]].push_back(mp[circulator->point()]);
          }
        }
      } while (++circulator != done);
    }

    bool bad = false;
    for (int i = 0; i < n; i++) {
      if (v[i].size() > 6) {
        bad = true;
        break;
      }

      for (int j = 0; j < v[i].size(); j++) {
        int next = v[i][j];
        for (int k = 0; k < v[next].size(); k++) {
          if (i != v[next][k] && CGAL::squared_distance(s[i], s[v[next][k]]) <= r) {
            bad = true;
          }
        }
      }
    }

    vector<int> col(n, -1);
    vector<int> comp(n, 0);

    int nrc = 0;
    for (int i = 0; i < n; i++) {
      if (col[i] == -1) {
        nrc++;
        comp[i] = nrc;
        bad = bad || dfs(i, col, 1, v, comp);
      }
    }

    vector<P> cp(m + m);
    for (int i = 0; i < m; i++) {
      cin >> cp[2 * i] >> cp[2 * i + 1];
    }

    for (int i = 0; i < m; i++) {
      P a = cp[2 * i], b = cp[2 * i + 1];

      P p1 = t.nearest_vertex(a)->point(), p2 = t.nearest_vertex(b)->point();
      long long d1 = CGAL::squared_distance(p1, a), d2 = CGAL::squared_distance(p2, b);

      if (bad) {
        cout << "n";
      } else {
        int start = mp[p1], end = mp[p2];

        long long d = CGAL::squared_distance(a, b);

        if (d <= r || (d1 <= r && d2 <= r && comp[start] == comp[end])) {

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
