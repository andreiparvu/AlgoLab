#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <cstdio>

using namespace std;
using namespace boost;

typedef pair<int, int> ii;

typedef adjacency_list<listS, vecS, undirectedS> Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

class dfs_critic : public default_dfs_visitor {
  public:
    dfs_critic(vector<ii> &sol, Graph &g) : m_sol(sol)  {
      m_height = vector<int>(num_vertices(g), 0);
      m_up = vector<int>(num_vertices(g), 0);
      m_pred = vector<int>(num_vertices(g), -1);

      m_indices = get(vertex_index, g);
    }

    void tree_edge(Edge e, const Graph &g) {
      int cur = m_indices[source(e, g)],
          next = m_indices[target(e, g)];

      m_pred[next] = cur;
      m_height[next] = m_height[cur] + 1;
      m_up[next] = m_height[next];
    }

    void back_edge(Edge e, const Graph &g) {
      int cur = m_indices[source(e, g)],
          next = m_indices[target(e, g)];

      if (m_pred[cur] != next) {
        m_up[cur] = min(m_up[cur], m_up[next]);
      }
    }

    void finish_vertex(Vertex v, const Graph &g) {
      int cur = m_indices[v];

      if (m_pred[cur] != -1) {
        m_up[m_pred[cur]] = min(m_up[m_pred[cur]], m_up[cur]);

        if (m_up[cur] > m_height[m_pred[cur]]) {
          m_sol.push_back(make_pair(
                min(cur, m_pred[cur]),
                max(cur, m_pred[cur])
                )
              );
        }
      }
    }

    vector<ii> &m_sol;
    vector<int> m_pred, m_height, m_up;
    property_map<Graph, vertex_index_t>::type m_indices;
};

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n, m;

    cin >> n >> m;

    vector<ii> edges(m);

    for (int i = 0; i < m; i++) {
      //cin >> edges[i].first >> edges[i].second;
      scanf("%d %d", &edges[i].first, &edges[i].second);
      edges[i].first--;
      edges[i].second--;
    }

    vector<ii> sol;

    Graph g(edges.begin(), edges.end(), n);

    dfs_critic vis(sol, g);
    depth_first_search(g, visitor(vis));

    cout << sol.size() << "\n";
    sort(sol.begin(), sol.end());

    for (int i = 0; i < sol.size(); i++) {
      cout << sol[i].first + 1 << " " << sol[i].second + 1 << "\n";
    }
  }

  return 0;
}

