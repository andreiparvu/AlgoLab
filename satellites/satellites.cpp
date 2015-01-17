#include <string>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <cassert>

#include <boost/graph/max_cardinality_matching.hpp>


/*
   1. maximum matching - select maximum number of edges such that no
   vertex has no adjacent edges
   2. minimum vertex cover - select a minimum number of nodes such that
   each edge has at leat one vertex at one of the ends
   3. maximum independent set - select a maximum number of vertices
   such that no two vertexes are connected through an edge

   Koning's theorem states that in a bipartite graph the size of the
   maximum matching equals the size of the minimum vertex cover.
   Secondly, the maximum independent set is the complement of a minimum
   vertex cover.

   To construct a minimum vertex cover:

  Take a maximum matching M and split the vertices in two sets, left (L)
  and right (R). Find unmatched vertices in L and mark them as visited.

  Start a dfs from visited vertices and:
    * traverse an edge from left to right if it's not a part of the 
    matching
    * traverse an edge from right to left if it's a part of the matching
  Label each vertex as visited.

  All unvisited in L and all visied in R form the minimum vertex cover
*/

using namespace std;
using namespace boost;

typedef adjacency_list<listS, vecS, undirectedS> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef property_map<Graph, vertex_index_t>::type IndexMap;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIt;

void dfs(int node, int n, Graph &g, vector<bool> &viz, vector<vector<bool> > &d) {
  OutEdgeIt ebeg, eend;

  tie(ebeg, eend) = out_edges(node, g);
  viz[node] = true;
  for (; ebeg != eend; ebeg++) {
    int next = target(*ebeg, g);

    if ((node < n && !d[node][next]) || (node >= n && d[node][next])) {
      if (!viz[next]) {
        dfs(next, n, g, viz, d);
      }
    }
  }
}

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n, m, l;

    cin >> n >> m >> l;

    vector<pair<int, int> > edges(l);

    for (int i = 0; i < l; i++) {
      cin >> edges[i].first >> edges[i].second;
      edges[i].second += n;
    }

    Graph gg(edges.begin(), edges.end(), n + m);

    vector<Vertex> mate(n + m);
    checked_edmonds_maximum_cardinality_matching(gg, &mate[0]);
    IndexMap indices = get(vertex_index, gg);

    vector<bool> viz(n + m, false);
    vector<vector<bool> > d(n + m, vector<bool>(n + m, false));

    for (int i = 0; i < n; i++) {
      if (mate[i] != graph_traits<Graph>::null_vertex()) {
        d[i][indices[mate[i]]] = d[indices[mate[i]]][i] = true;
      } else {
        viz[i] = true;
      }
    }

    for (int i = 0; i < n; i++) {
      if (viz[i]) {
        dfs(i, n, gg, viz, d);
      }
    }

    vector<int> g, s;
    for (int i = 0; i < n; i++) {
      if (!viz[i]) {
        g.push_back(i);
      }
    }
    for (int i = 0; i < m; i++) {
      if (viz[n + i]) {
        s.push_back(i);
      }
    }

    cout << g.size() << " " << s.size() << "\n";
    for (int i = 0; i < g.size(); i++) {
      cout << g[i] << " ";
    }
    for (int i = 0; i < s.size(); i++) {
      cout << s[i] << " ";
    }
    cout << "\n";
  }

  return 0;
}

