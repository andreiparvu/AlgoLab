#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <cstdio>
#include <boost/graph/strong_components.hpp>

using namespace std;
using namespace boost;

typedef pair<int, int> ii;

typedef adjacency_list<listS, vecS, directedS> Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int n, m;

    cin >> n >> m;

    vector<ii> edges(m);

    for (int i = 0; i < m; i++) {
      cin >> edges[i].second >> edges[i].first;
      edges[i].second--;
      edges[i].first--;
    }

    vector<int> cost(n);
    for (int i = 0; i < n; i++) {
      cin >> cost[i];
    }

    Graph g(edges.begin(), edges.end(), n);

    vector<int> scc(n);
    int nrc = strong_components(g, &scc[0]);

    vector<bool> isFinal(nrc, true);
    for (int i = 0; i < m; i++) {
      if (scc[edges[i].first] != scc[edges[i].second]) {
        isFinal[scc[edges[i].first]] = false;
      }
    }

    vector<int> rez(nrc, 101);

    for (int i = 0; i < n; i++) {
      if (isFinal[scc[i]] && cost[i] < rez[scc[i]]) {
        rez[scc[i]] = cost[i];
      }
    }

    int sum = 0;
    for (int i = 0; i < nrc; i++) {
      sum += rez[i] != 101 ? rez[i] : 0;
    }

    cout << sum << "\n";
  }

  return 0;
}

