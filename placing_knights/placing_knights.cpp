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

const int cntx[] = {-1, -1, 1, 1, -2, -2, 2, 2},
          cnty[] = {-2, 2, -2, 2, -1, 1, -1, 1};

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
    int n;
    cin >> n;

    vector<vector<int> > v(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> v[i][j];
      }
    }

    Graph g(n * n + 2);
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap revEdge = get(edge_reverse, g);

    int nrs = 0;
    int source = n * n, sink = n * n + 1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (v[i][j] == 0) {
          continue;
        }
        nrs++;
        if ((i + j) % 2 == 0) {
          for (int k = 0; k < 8; k++) {
            int ii = i + cntx[k], jj = j + cnty[k];

            if (ii >= 0 && ii < n && jj >= 0 && jj < n && v[ii][jj] == 1) {
              addEdge(i * n + j, ii * n + jj, 1, g, capacity, revEdge);
            }
          }
          addEdge(source, i * n + j, 1, g, capacity, revEdge);
        } else {
          addEdge(i * n + j, sink, 1, g, capacity, revEdge);
        }
      }
    }

    cout << nrs - push_relabel_max_flow(g, *(vertices(g).first + source),
                                     *(vertices(g).first + sink)) << "\n";
  }

  return 0;
}

