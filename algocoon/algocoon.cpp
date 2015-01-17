#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>
#include <cstdio>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <queue>

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

    Graph g(n);
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap revEdge = get(edge_reverse, g);
    property_map<Graph, edge_residual_capacity_t>::type 
      residual_capacity = get(edge_residual_capacity, g);
    vector<vector<int> > cap(n, vector<int>(n, 0));

    for (int i = 0; i < m; i++) {
      int x, y, c;

      cin >> x >> y >> c;

      addEdge(x, y, c, g, capacity, revEdge);
    }

    int rez = -1;
    int p1, p2;
    for (int i = 1; i < n; i++) {
      int flow = push_relabel_max_flow(g, *vertices(g).first,
                                  *(vertices(g).first + i));

      int flow2 = push_relabel_max_flow(g, *(vertices(g).first + i),
                                  *vertices(g).first);
      if (rez == -1 || flow < rez) {
        rez = flow;
        p1 = 0, p2 = i;
      }
      if (flow2 < rez) {
        rez = flow2;
        p1 = i, p2 = 0;
      }
    }


    cout << rez << "\n";

    push_relabel_max_flow(g, *(vertices(g).first + p1),
                                  *(vertices(g).first + p2));

    std::queue<int> q;
    q.push(p1);
    vector<bool> fst(n, false);
    fst[p1] = true;

    vector<int> sol;
    while (!q.empty()) {
      int x = q.front();
      q.pop();

      sol.push_back(x);
      graph_traits<Graph>::out_edge_iterator ei, e_end;
      for (tie(ei, e_end) = out_edges(*(vertices(g).first + x), g); ei != e_end; ++ei) {
        if (capacity[*ei] > 0 && residual_capacity[*ei] > 0 && fst[target(*ei, g)] == false) {
          fst[target(*ei, g)] = true;
          q.push(target(*ei, g));
        }
      }
    }

    cout << sol.size();
    for (int i = 0; i < sol.size(); i++) {
      cout << " " << sol[i];
    }
    cout << "\n";



  }

  return 0;
}

