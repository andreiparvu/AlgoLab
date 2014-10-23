#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <cstdio>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
        property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;

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
  int tests;

  cin >> tests;

  while (tests--) {
    int n, m;

    cin >> n >> m;

    Graph g(n + m + 2);

    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap revEdge = get(edge_reverse, g);

    vector<int> s(n);

    int source = n + m, sink = n + m + 1;
    int nrm = 0;
    for (int i = 0; i < m; i++) {
      int a, b, c;
      cin >> a >> b >> c;

      if (c == 1) {
        s[a]--;
      } else if (c == 2) {
        s[b]--;
      } else {
        nrm++;
        addEdge(source, n + i, 1, g, capacity, revEdge);
        addEdge(n + i, a, 1, g, capacity, revEdge);
        addEdge(n + i, b, 1, g, capacity, revEdge);
      }
    }

    int sum = 0;
    bool bad = false;
    for (int i = 0; i < n; i++) {
      int a;
      cin >> a;
      s[i] += a;

      addEdge(i, sink, s[i], g, capacity, revEdge);
      sum += s[i];

      if (s[i] < 0) {
        bad = true;
      }
    }

    int flow = 0;
    if (!bad) {
      flow = push_relabel_max_flow(g, *(vertices(g).first + source),
                          *(vertices(g).first + sink));
    }

    if (flow == sum && flow == nrm && bad == false) {
      cout << "yes\n";
    } else {
      cout << "no\n";
    }
  }

  return 0;
}

