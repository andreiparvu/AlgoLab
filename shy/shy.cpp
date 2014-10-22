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
    int n, m;
    scanf("%d%d", &n, &m);

    vector<pair<int, int> > edges(m + n);
    for (int i = 0; i < m; i++) {
      scanf("%d%d", &edges[i].first, &edges[i].second);
    }

    for (int i = 0; i < n; i++) {
      edges[m + i].first = n;
      edges[m + i].second = i;
    }

    Graph g(edges.begin(), edges.end(), n + 1);

    bool ok = boyer_myrvold_planarity_test(g);

    if (!ok) {
      printf("no\n");
    } else {
      printf("yes\n");
    }
  }

  return 0;
}

