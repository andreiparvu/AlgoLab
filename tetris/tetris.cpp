#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
            property<edge_capacity_t, int,
              property<edge_residual_capacity_t, int,
                property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;

const int inf = 0x3f3f3f3f;

void addEdge(int a, int b, int c, Graph &g, EdgeCapacityMap &capacity,
    ReverseEdgeMap &revEdge) {
  Edge e, reverseE;
  tie(e, tuples::ignore) = add_edge(a, b, g);
  tie(reverseE, tuples::ignore) = add_edge(b, a, g);
  capacity[e] = c;
  capacity[reverseE] = 0;
  revEdge[e] = reverseE;
  revEdge[reverseE] = e;
}

int main() {
  int nr_tests;

  cin >> nr_tests;

  while (nr_tests--) {
    int w, n;
    cin >> w >> n;

    Graph g(2 * w);
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap revEdge = get(edge_reverse, g);

    for (int i = 1; i < w; i++) {
      int x = 2 * i, y = 2 * i + 1;

      addEdge(x, y, 1, g, capacity, revEdge);
    }

    addEdge(0, 1, inf, g, capacity, revEdge);
    addEdge(2 * w, 2 * w + 1, inf, g, capacity, revEdge);

    for (int i = 0; i < n; i++) {
      int x, y;

      cin >> x >> y;

      int xx = min(x, y), yy = max(x, y);
      addEdge(2 * xx + 1, 2 * yy, 1, g, capacity, revEdge);
    }

    int source = 0, sink = 2 * w + 1;
    cout << push_relabel_max_flow(g, *(vertices(g).first + source),
                                     *(vertices(g).first + sink)) << "\n";
  }

  return 0;
}

