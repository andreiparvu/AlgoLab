#include <iostream>
#include <cstdio>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <vector>

using namespace std;

#ifdef CGAL_USE_GMP

#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;

#else

#include <CGAL/MP_Float.h>

typedef CGAL::MP_Float ET;

#endif

// program and solution types

typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


int main() {
  for (;;) {
    int n, m;

    cin >> n >> m;

    if (!n && !m) {
      break;
    }

    vector<pair<int, int> > cant(n);

    for (int i = 0; i < n; i++) {
      cin >> cant[i].first >> cant[i].second;
    }


    Program qp(CGAL::SMALLER, true, 0, false, 0);

    for (int i = 0; i < m; i++) {
      int cost;

      cin >> cost;
      for (int j = 0; j < n; j++) {
        int quant;
        cin >> quant;

        qp.set_a(i, j, quant);
        qp.set_a(i, n + j, quant);
      }

      qp.set_c(i, cost);
    }

    for (int i = 0; i < n; i++) {
      qp.set_b(i, cant[i].second);

      qp.set_b(n + i, cant[i].first);
      qp.set_r(n + i, CGAL::LARGER);
    }

    Solution s = CGAL::solve_quadratic_program(qp, ET());

    if (s.is_infeasible()) {
      cout << "No such diet.\n";
    } else {
      int res = floor(CGAL::to_double(s.objective_value()));
      cout << (res == 0 ? 0 : res) << "\n";
    }

  }

  return 0;
}

