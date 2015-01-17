#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 P;

long my_ceil(K::FT a) {
  double x = ceil(CGAL::to_double(a));
  while (x < a) {
    x++;
  }
  while (x-1 >= a) {
    x--;
  }
  return (long)x;
}

int main() {
  ios::sync_with_stdio(false);

  int tests;

  cin >> tests;

  while (tests--) {
    int n;

    cin >> n;

    vector<P> points(n);
    vector<pair<K::FT, int>> dist(n);
    vector<P> pts(n);
    for (int i = 0; i < n; i++) {
      cin >> points[i];

      dist[i] = make_pair(CGAL::squared_distance(points[i], points[0]), i);
    }

    sort(dist.begin(), dist.end());

    for (int i = 0; i < n; i++) {
      pts[i] = points[dist[i].second];
    }

    int li = 1, ls = n - 1, found;
    K::FT curDist;
    while (li <= ls) {
      int cur = (li + ls) / 2;

      Min_circle mc(pts.begin() + cur, pts.end(), true);

      if (mc.circle().squared_radius() <= dist[cur - 1].first) {
        found = cur;
        curDist = dist[cur - 1].first;
        ls = cur - 1;
      } else {
        li = cur + 1;
      }
    }


    Min_circle mc(pts.begin() + found - 1, pts.end(), true);
    if (mc.circle().squared_radius() < curDist) {
      cout << my_ceil(mc.circle().squared_radius()) << "\n";
    } else {
      cout << my_ceil(curDist) << "\n";
    }
  }

  return 0;
}
