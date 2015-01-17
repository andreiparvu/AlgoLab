#include <iostream>
#include <cstdio>
#include <cassert>
#include <CGAL/basic.h> 
#include <CGAL/QP_models.h> 
#include <CGAL/QP_functions.h> 
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Ray_2 R;
typedef K::Point_2 P;
typedef K::Segment_2 S;

#ifdef CGAL_USE_GMP

#include <CGAL/Gmpzf.h>
typedef CGAL::Gmpzf ET;
  
#else
  
#include <CGAL/MP_Float.h>
    
typedef CGAL::MP_Float ET;
    
#endif

typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
  int tests;

  cin >> tests;

  while (tests--) {
    int l, s, w;

    cin >> l >> s >> w;

    Program qp(CGAL::SMALLER, true, 1, true, 4096);

    vector<P> lamp(l);

    for (int i = 0; i < l; i++) {
      cin >> lamp[i];
    }

    vector<P> stamp(s);

    for (int i = 0; i < s; i++) {
      double mx;

      cin >> stamp[i];
      cin >> mx;

      qp.set_b(i, mx);
      qp.set_b(s + i, 1);
      qp.set_r(s + i, CGAL::LARGER);
    }

    vector<S> walls(w);

    for (int i = 0; i < w; i++) {
      P p1, p2;
      cin >> p1 >> p2;

      walls[i] = S(p1, p2);
    }

    for (int i = 0; i < s; i++) {
      for (int j = 0; j < l; j++) {
        S seg(stamp[i], lamp[j]);

        bool inter = false;
        for (int k = 0; k < w; k++) {
          if (CGAL::do_intersect(seg, walls[k])) {
            inter = true;
            break;
          }
        }

        if (inter) {
          qp.set_a(j, i, 0);
          qp.set_a(j, s + i, 0);
        } else {
          qp.set_a(j, i, 1 / CGAL::to_double(CGAL::squared_distance(stamp[i], lamp[j])));
          qp.set_a(j, s + i, 1 / CGAL::to_double(CGAL::squared_distance(stamp[i], lamp[j])));
        }
      }
    }

    for (int i = 0; i < l; i++) {
      qp.set_c(i, 1);
    }

    Solution sol = CGAL::solve_linear_program(qp, ET());

    if (sol.is_infeasible()) {
      cout << "no\n";
    } else {
      cout << "yes\n";
    }
  }

  return 0;
}

