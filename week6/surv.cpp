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

typedef graph_traits<Graph>::vertex_descriptor Vertex;

int inf = 1000000;

class my_bfs : public default_bfs_visitor {
  public:
    my_bfs(vector<int> &seen, Graph &g) : m_seen(seen)  {
      m_indices = get(vertex_index, g);
    }

    void discover_vertex(Vertex v, const Graph &g) {
      m_seen[m_indices[v]] = 1;

      //fprintf(stderr, "yes %d\n", m_indices[v]);
    }
   
    vector<int> &m_seen;
    property_map<Graph, vertex_index_t>::type m_indices;
};

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
    int n, m, k, l;

    cin >> n >> m >> k >> l;

    vector<int> police(k), photo(l), cntPhoto(n, 0), isPolice(n, 0);
    vector<vector<int> > cnt(n, vector<int>(n, 0));

    for (int i = 0; i < k; i++) {
      cin >> police[i];

      isPolice[police[i]]++;
    }

    for (int i = 0; i < l; i++) {
      cin >> photo[i];

      cntPhoto[photo[i]]++;
    }

    for (int i = 0; i < m; i++) {
      int x, y;
      cin >> x >> y;

      cnt[x][y]++;
    }

    Graph g(n + 2 + k + l);
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap revEdge = get(edge_reverse, g);

    int source = n + k + l;
    int sink = n + k + l + 1;

    vector<pair<int, int> > edges;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (cnt[i][j] > 0) {
          addEdge(i, j, cnt[i][j], g, capacity, revEdge);
          edges.push_back(make_pair(i, j));
        }
      }
    }

    Graph gg(edges.begin(), edges.end(), n);

    for (int i = 0; i < k; i++) {
      //fprintf(stderr, "==\n");
      vector<int> seen(n, 0);

      my_bfs vis(seen, gg);

      breadth_first_search(gg, vertex(police[i], g), visitor(vis));

      vector<int> nodes(n, 0);

      for (int j = 0; j < l; j++) {
        if (seen[photo[j]] > 0) {
          addEdge(n + i, n + k + j, 1, g, capacity, revEdge);

          //fprintf(stderr, "new edge %d %d\n", police[i], j);
        }
      }

      addEdge(source, n + i, 1, g, capacity, revEdge);
    }

    for (int i = 0; i < l; i++) {
      if (cntPhoto[photo[i]] > 0) {
        addEdge(n + k + i, photo[i], cntPhoto[photo[i]], g, capacity, revEdge);
        //fprintf(stderr, "--%d\n", cntPhoto[photo[i]]);

        cntPhoto[photo[i]] = 0;
      }
    }

    for (int i = 0; i < n; i++) {
      if (isPolice[i] > 0) {
        addEdge(i, sink, isPolice[i], g, capacity, revEdge);
      }
    }

    cout << push_relabel_max_flow(g, *(vertices(g).first + source),
                                  *(vertices(g).first + sink)) << "\n";
  }

  return 0;
}

