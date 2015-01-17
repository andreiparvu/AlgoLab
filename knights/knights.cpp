#include <iostream>
#include <cstdio>
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

const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};

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
    int n, m, t;

    cin >> n >> m >> t;

    n += 2;
    m += 2;
    Graph g(n * m * 2 + 2);
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap revEdge = get(edge_reverse, g);

    int source = n * m * 2, sink = n * m * 2 + 1;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        int node = i * m + j;

        if (i > 0 && i < n - 1 && j > 0 && j < m - 1) {
          for (int k = 0; k < 4; k++) {
            int ii = i + dx[k], jj = j + dy[k];

            if (ii >= 0 && ii < n && jj >= 0 && jj < m) {
              int next = ii * m + jj;

              addEdge(2 * node + 1, 2 * next, 1, g, capacity, revEdge);
            }
          }
        }

        addEdge(2 * node, 2 * node + 1, 1, g, capacity, revEdge);
      }
    }
    
    for (int i = 1; i < n - 1; i++) {
      int node = i * m + 0;
      addEdge(2 * node + 1, sink, 1, g, capacity, revEdge);
      node = i * m + m - 1;
      addEdge(2 * node + 1, sink, 1, g, capacity, revEdge);
    }

    for (int j = 1; j < m - 1; j++) {
      int node = 0 * m + j;
      addEdge(2 * node + 1, sink, 1, g, capacity, revEdge);
      node = (n - 1) * m + j;
      addEdge(2 * node + 1, sink, 1, g, capacity, revEdge);
    }

    for (int i = 0; i < t; i++) {
      int x, y;
      cin >> x >> y;
      x++;
      y++;

      addEdge(source, 2 * (x * m + y), 1, g, capacity, revEdge);
    }

    cout << push_relabel_max_flow(g, *(vertices(g).first + source),
                                     *(vertices(g).first + sink)) << "\n";
  }

  return 0;
}

