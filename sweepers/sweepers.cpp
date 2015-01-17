#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <cstdio>
//#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/graph/connected_components.hpp>

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

typedef adjacency_list<listS, vecS, undirectedS, no_property> G;

int main() {
  int nr_tests;

  cin >> nr_tests;

  while (nr_tests--) {
    int n, m, s;

    cin >> n >> m >> s;

    Graph g(n + 2);
    G gg(n);
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap revEdge = get(edge_reverse, g);

    int source = n;
    int sink = n + 1;

    vector<int> cnt(n, 0), exit(n, 0), entrance(n, 0);

    for (int i = 0; i < s; i++) {
      int x;
      cin >> x;

      entrance[x]++;
      cnt[x]++;
    }
    for (int i = 0; i < s; i++) {
      int x;
      cin >> x;

      exit[x]++;
      cnt[x]++;
    }

    for (int i = 0; i < m; i++) {
      int x, y;

      cin >> x >> y;

      cnt[x]++;
      cnt[y]++;

      addEdge(x, y, 1, 1, g, capacity, revEdge);
      add_edge(x, y, gg);
    }

    bool bad = false;
    for (int i = 0; i < n; i++) {
      if (cnt[i] % 2 == 1) {
        bad = true;
      }
    }

    for (int i = 0; i < n; i++) {
      if (entrance[i] > 0) {
        addEdge(source, i, entrance[i], 0, g, capacity, revEdge);
      }
      if (exit[i] > 0) {
        addEdge(i, sink, exit[i], 0, g, capacity, revEdge);
      }
    }

    vector<int> component(n);
    int num = connected_components(gg, &component[0]);
    vector<int> comp(num), nrv(num, 0);
    int nrc = 0;

    for (int i = 0; i < n; i++) {
      nrv[component[i]]++;
    }

    for (int i = 0; i < n; i++) {
      if (entrance[i]) {
        if (comp[component[i]] == 0) {
          nrc++;
          comp[component[i]] = 1;
        }
      } else if (nrv[component[i]] == 1) {
        nrc++;
      }
    }

    int flow = edmonds_karp_max_flow(g, *(vertices(g).first + source),
                            *(vertices(g).first + sink));
    if (bad == true || flow != s || nrc != num) {
      cout << "no\n";
    } else {
      cout << "yes\n";
    }
  }

  return 0;
}
