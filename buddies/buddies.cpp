#include <string>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <cassert>
#include <set>

#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
            property<edge_capacity_t, int,
              property<edge_residual_capacity_t, int,
                property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;


typedef adjacency_list<vecS, vecS, undirectedS> G;
typedef graph_traits<G>::vertex_descriptor Vertex;
typedef property_map<G, vertex_index_t>::type IndexMap;


typedef graph_traits<G>::out_edge_iterator OutEdgeIt;


bool dfs(int node, int c, vector<int> &cols, G &g) {
  OutEdgeIt ebeg, eend;
  tie(ebeg, eend) = out_edges(node, g);

  bool sol = true;
  for (; ebeg != eend; ebeg++) {
    int next = target(*ebeg, g);

    if (cols[next] == -1) {
      cols[next] = 1 - c;

      sol = sol && dfs(next, 1 - c, cols, g);
    } else if (cols[next] != 1 - c) {
      return false;
    }
  }

  return sol;
}

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
    int n, c, f;

    cin >> n >> c >> f;

    vector<set<string> > car(n, set<string>());

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < c; j++) {
        string s;
        cin >> s;

        car[i].insert(s);
      }
    }


    vector<bool> ok(n, false);
    int nrs = 0;
    vector<pair<int, int> > my_edges;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int nr = 0;
        for (set<string>::iterator it = car[i].begin(); it != car[i].end();
            it++) {
          if (car[j].find(*it) != car[j].end()) {
            nr++;
          }
        }

        if (nr > f) {
          my_edges.push_back(make_pair(i, j));
          if (!ok[i]) {
            ok[i] = true;
            nrs++;
          }
          if (!ok[j]) {
            ok[j] = true;
            nrs++;
          }
        }
      }

    }

    G g(my_edges.begin(), my_edges.end(), n);
    IndexMap indices = get(vertex_index, g);

    vector<int> cols(n, -1);

    int flow;

    bool bip = true;
    for (int i = 0; i < n; i++) {
      if (cols[i] == -1) {
        bip = bip && dfs(i, 0, cols, g);
      }
    }

    if (bip) {
      Graph gg(n + 2);

      EdgeCapacityMap capacity = get(edge_capacity, gg);
      ReverseEdgeMap revEdge = get(edge_reverse, gg);

      int source = n, sink = n + 1;

      for (int i = 0; i < my_edges.size(); i++) {
        if (cols[my_edges[i].first] == 0) {
          addEdge(my_edges[i].first, my_edges[i].second, 1, gg, capacity, revEdge);
        } else {
          addEdge(my_edges[i].second, my_edges[i].first, 1, gg, capacity, revEdge);
        }
      }

      for (int i = 0; i < n; i++) {
        if (cols[i] == 0) {
          addEdge(source, i, 1, gg, capacity, revEdge);
        } else {
          addEdge(i, sink, 1, gg, capacity, revEdge);
        }
      }

      flow = push_relabel_max_flow(gg, *(vertices(gg).first + source),
                                  *(vertices(gg).first + sink));
    } else {
      vector<Vertex> mate(n);
      checked_edmonds_maximum_cardinality_matching(g, &mate[0], indices);
      flow = matching_size(g, &mate[0]);
    }

    if (nrs != n && my_edges.size() <= n / 2) {
      cout << "optimal\n";
      continue;
    }

    if (flow == n / 2) {
      cout << "not optimal\n";
    } else {
      cout << "optimal\n";
    }
  }

  return 0;
}

