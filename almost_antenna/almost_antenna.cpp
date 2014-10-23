#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef K::Point_2 P;

int main() {
  for (;;) {
    int n;

    cin >> n;

    if (!n) {
      break;
    }

    vector<P> v(n);

    for (int i = 0; i < n; i++) {
      long x, y;

      cin >> x >> y;
      v[i] = P(x, y);
    }

    Min_circle mc(v.begin(), v.end(), true);
    Traits::Circle c = mc.circle();

    int nrp = mc.number_of_support_points();

    CORE::BigInt sol = ceil(sqrt(mc.circle().squared_radius()));
    if (nrp <= 3) {
      for (int i = 0; i < nrp; i++) {
        vector<P> w;
        bool done = false;
        for (int j = 0; j < n; j++) {
          if (!done && v[j] == mc.support_point(i)) {
            done = true;
          } else {
            w.push_back(v[j]);
          }
        }

        Min_circle mc1(w.begin(), w.end(), true);

        sol = min(sol, ceil(sqrt(mc1.circle().squared_radius())));
      }
    }

    cout << sol << "\n";

  }

  return 0;
}

