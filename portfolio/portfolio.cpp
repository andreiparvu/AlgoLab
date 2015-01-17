#include <iostream>
#include <cstdio>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <vector>

using namespace std;

#ifdef CGAL_USE_GMP

#include <CGAL/Gmpzf.h>
typedef CGAL::Gmpzf ET;

#else

#include <CGAL/MP_Float.h>

typedef CGAL::MP_Float ET;

#endif

// program and solution types

typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
  for (;;) {
    int n, m;
    cin >> n >> m;

    if (!n && !m) {
      return 0;
    }

    Program qp(CGAL::LARGER, true, 0, false, 0);

    vector<int> cost(n), ret(n);
    for (int i = 0; i < n; i++) {
      cin >> cost[i] >> ret[i];

      qp.set_a(i, 0, (double)ret[i] / cost[i]);
      qp.set_a(i, 1, 1);
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        int val;

        cin >> val;

        if (j <= i) {
          qp.set_d(i, j, 2 * ((double)val / (cost[i] * cost[j])));
        }
      }
    }

    for (int i = 0; i < m; i++) {
      int c, r, v;

      cin >> c >> r >> v;

      qp.set_b(1, c);
      qp.set_r(1, CGAL::SMALLER);

      qp.set_b(0, r);

      Solution s = CGAL::solve_quadratic_program(qp, ET());

      if (s.is_infeasible() || CGAL::to_double(s.objective_value()) > v) {
        cout << "No.\n";
      } else {
        cout << "Yes.\n";
      }
    }

  }

  return 0;
}

