#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

using namespace std;
using namespace boost;


typedef adjacency_list<listS, vecS, undirectedS, no_property,
      property<edge_weight_t, int> > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n, m;

    cin >> n >> m;

    vector<pair<int, int> > edges;
    vector<int> weights;

    for (int i = 0; i < m; i++) {
      int x, y, c;

      cin >> x >> y >> c;

      edges.push_back(make_pair(x, y));
      weights.push_back(c);
    }

    adjacency_list<listS, vecS, undirectedS, no_property,
      property<edge_weight_t, int> > g(edges.begin(), edges.end(),
                                       weights.begin(), n);

    vector<Edge> mst_edges(n - 1);

    property_map<Graph, edge_weight_t>::type weight = get(edge_weight, g);

    kruskal_minimum_spanning_tree(g, mst_edges.begin());

    int sum = 0;
    for (vector<Edge> :: iterator ei = mst_edges.begin(); ei != mst_edges.end();
        ei++) {
      sum += weight[*ei];
    }

    vector<int> dist(n);
    dijkstra_shortest_paths(g, *(vertices(g).first), distance_map(&dist[0]));

    int mDist = 0;
    for (int i = 0; i < n; i++) {
      mDist = max(mDist, dist[i]);
    }

    cout << sum << " " << mDist << "\n";

  }

  return 0;
}
