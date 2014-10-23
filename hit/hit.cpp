#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <iostream>
#include <stdexcept>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef K::Ray_2 R;
typedef K::Point_2 P;
typedef K::Segment_2 S;

int main() {
  for (;;) {
    int n;
    cin >> n;

    if (!n) {
      break;
    }

    long x, y, a, b;

    cin >> x >> y >> a >> b;
    P s(x, y);
    R ray(P(x, y), P(a, b));

    bool intersect = false;
    while (n--) {
      long r, s, t, u;
      cin >> r >> s >> t >> u;

      S seg(P(r, s), P(t, u));

      intersect = intersect || CGAL::do_intersect(seg, ray);
    }

    if (!intersect) {
      cout << "no\n";
    } else {
      cout << "yes\n";
    }
  }

  return 0;
}

