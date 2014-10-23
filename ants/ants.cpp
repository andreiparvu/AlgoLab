#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <cstdio>

using namespace std;
using namespace boost;

typedef adjacency_list<listS, vecS, undirectedS, no_property,
  property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;

typedef pair<int, int> ii;

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n, m, species, start, end;

    cin >> n >> m >> species >> start >> end;

    vector<ii> edges(m);
    vector<vector<int> > weights(species, vector<int>(m));

    for (int i = 0; i < m; i++) {
      cin >> edges[i].first >> edges[i].second;
      for (int j = 0; j < species; j++) {
        cin >> weights[j][i];
      }
    }
    for (int i = 0; i < species; i++) {
      int x;
      cin >> x;
    }

    vector<ii> final_edges;
    vector<int> final_weights;

    for (int i = 0; i < species; i++) {
      Graph g(Graph(edges.begin(), edges.end(), weights[i].begin(), n));
      property_map<Graph, vertex_index_t>::type index = get(vertex_index, g);
      property_map<Graph, edge_weight_t>::type weight = get(edge_weight, g);

      vector<Edge> mst_edges(n - 1);

      kruskal_minimum_spanning_tree(g, mst_edges.begin());

      for (vector<Edge>::iterator ei = mst_edges.begin(); ei != mst_edges.end();
          ei++) {
        final_edges.push_back(make_pair(index[source(*ei, g)],
              index[target(*ei, g)]));

        final_weights.push_back(weight[*ei]);
      }
    }

    Graph finalG(final_edges.begin(), final_edges.end(), final_weights.begin(), n);

    vector<int> dist(n);
    dijkstra_shortest_paths(finalG, *(vertices(finalG).first + start),
        distance_map(&dist[0]));

    cout << dist[end] << "\n";
  }

  return 0;
}

