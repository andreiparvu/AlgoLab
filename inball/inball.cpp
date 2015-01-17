#include <iostream>
#include <cstdio>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

using namespace std;

#ifdef CGAL_USE_GMP

#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;

#else

#include <CGAL/MP_Float.h>

typedef CGAL::MP_Float ET;

#endif

typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
  ios::sync_with_stdio(false);
  while (true) {
    int n, d;

    cin >> n;

    if (!n) {
      break;
    }

    cin >> d;

    int R = d;
    Program qp(CGAL::SMALLER, false, 0, false, 0);
    for (int i = 0; i < n; i++) {
      int sum = 0;

      for (int j = 0; j < d; j++) {
        int a;

        cin >> a;

        qp.set_a(j, i, a);
        qp.set_a(j, n + i, a);

        sum += a * a;
      }

      int b;
      cin >> b;

      qp.set_a(R, n + i, int(sqrt(sum)));

      qp.set_b(i, b);
      qp.set_b(i + n, b);
    }

    qp.set_c(R, -1);

    Solution s = CGAL::solve_linear_program(qp, ET());

    if (s.is_infeasible()) {
      cout << "none\n";
    } else if (s.is_unbounded()) {
      cout << "inf\n";
    } else {
      cout << abs(ceil(CGAL::to_double(s.objective_value()))) << "\n";
    }
  }

  return 0;
}

