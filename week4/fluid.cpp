#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/property_map/property_map.hpp>
#include <vector>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <cstdio>
#include <boost/graph/planar_face_traversal.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list<listS, vecS, undirectedS> Graph;

int main() {
  int tests;

  scanf("%d", &tests);

  while (tests--) {
    int m;
    scanf("%d", &m);

    vector<vector<int> > v(m, vector<int>(m - 1));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m - 1; j++) {
        scanf("%d", &v[i][j]);
      }
    }

    int li = 0, ls = m - 2, rez = -1;

    while (li <= ls) {
      int mid = (li + ls) / 2;

      vector<pair<int, int> > edges;

      for (int i = 0; i < m; i++) {
        for (int j = 0; j <= mid; j++) {
          edges.push_back(make_pair(i, v[i][j]));
        }
      }

      Graph g(edges.begin(), edges.end(), m);

      bool ok = boyer_myrvold_planarity_test(g);

      if (ok) {
        rez = mid;
        li = mid + 1;
      } else {
        ls = mid - 1;
      }
    }

    printf("%d\n", rez + 1);
  }

  return 0;
}

