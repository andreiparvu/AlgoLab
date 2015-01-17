#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <cstdio>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/breadth_first_search.hpp>

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

const int INF = 0x3f3f3f3f;

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
  int nrTests;

  cin >> nrTests;

  while (nrTests--) {
    int Z, J;

    cin >> Z >> J;

    Graph g(Z + J + 2);
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap revEdge = get(edge_reverse, g);

    int source = Z + J, sink = Z + J + 1;
    for (int i = 0; i < Z; i++) {
      int c;
      cin >> c;

      addEdge(source, i, c, g, capacity, revEdge);
    }

    int res = 0;

    for (int i = 0; i < J; i++) {
      int c;
      cin >> c;

      addEdge(Z + i, sink, c, g, capacity, revEdge);

      res += c;
    }

    for (int i = 0; i < J; i++) {
      int nr;

      cin >> nr;

      for (int j = 0; j < nr; j++) {
        int z;
        cin >> z;

        addEdge(z - 1, Z + i, INF, g, capacity, revEdge);
      }
    }

    cout << res - push_relabel_max_flow(g, *(vertices(g).first + source),
                                  *(vertices(g).first + sink)) << "\n";
  }

  return 0;
}

