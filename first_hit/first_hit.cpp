#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <stdexcept>
#include <algorithm>
#include <iostream>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;

typedef K::Ray_2 R;
typedef K::Point_2 P;
typedef K::Segment_2 S;

int main() {
  ios_base::sync_with_stdio(false);

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

    K::FT rez = -1;
    P pt(0, 0);

    while (n--) {
      long r, s, t, u;
      cin >> r >> s >> t >> u;

      S seg(P(r, s), P(t, u));

      auto result = CGAL::intersection(seg, ray);

      if (result != NULL) {
        if (const S *is = boost::get<S>(&*result)) {
          if (CGAL::squared_distance(P(x, y), is->source()) < rez || rez == -1) {
            rez = CGAL::squared_distance(P(x, y), is->source());
            pt = is->source();
          }

          if (CGAL::squared_distance(P(x, y), is->target()) < rez || rez == -1) {
            rez = CGAL::squared_distance(P(x, y), is->target());
            pt = is->target();
          }
        } else if (const P *ip = boost::get<P>(&*result)) {
          if (CGAL::squared_distance(P(x, y), *ip) < rez || rez == -1) {
            rez = CGAL::squared_distance(P(x, y), *ip);
            pt = *ip;
          }
        }
      }
    }

    if (rez == -1) {
      cout << "no\n";
    } else {
      cout << floor(pt.x()) << " " << floor(pt.y()) << "\n";
    }
  }

  return 0;
}

