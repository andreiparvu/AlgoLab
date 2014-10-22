#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <cstdio>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace boost;
using namespace std;

const int INF = 0x3f3f3f3f;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
            property<edge_capacity_t, int,
              property<edge_residual_capacity_t, int,
                property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;

void addEdge(int a, int b, int c, int crev, Graph &g, EdgeCapacityMap &capacity,
    ReverseEdgeMap &revEdge) {
  Edge e, reverseE;
  tie(e, tuples::ignore) = add_edge(a, b, g);
  tie(reverseE, tuples::ignore) = add_edge(b, a, g);
  capacity[e] = c;
  capacity[reverseE] = crev;
  revEdge[e] = reverseE;
  revEdge[reverseE] = e;
}

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n, m;

    cin >> n >> m;

    int source = n, sink = n + 1;
    int vSource = n + 2, vSink = n + 3;

    Graph g(n + 4);

    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap revEdge = get(edge_reverse, g);

    vector<int> supIn(n + 2, 0), supOut(n + 2, 0);

    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;

      supOut[i] += y;
      supIn[sink] += y;

      addEdge(source, i, x, 0, g, capacity, revEdge);
      addEdge(i, sink, INF, 0, g, capacity, revEdge);
    }
    for (int i = 0; i < m; i++) {
      int x, y, c, csup;
      cin >> x >> y >> c >> csup;

      supOut[x] += c;
      supIn[y] += c;

      addEdge(x, y, csup - c, 0, g, capacity, revEdge);
    }

    int expected = 0;
    for (int i = 0; i <= sink; i++) {
      addEdge(vSource, i, supIn[i], 0, g, capacity, revEdge);
      addEdge(i, vSink, supOut[i], 0, g, capacity, revEdge);

      expected += supIn[i];
    }

    addEdge(source, sink, INF, INF, g, capacity, revEdge);

    int flow = push_relabel_max_flow(g, *(vertices(g).first + vSource),
                                  *(vertices(g).first + vSink));

    if (flow == expected) {
      cout << "yes\n";
    } else {
      cout << "no\n";
    }
  }

  return 0;
}

