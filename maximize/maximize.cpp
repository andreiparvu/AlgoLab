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

// program and solution types

typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void solve_max(Solution *s, int a, int b) {
  Program qp(CGAL::SMALLER, true, 0, false, 0);

  const int X = 0;
  const int Y = 1;

  qp.set_a(X, 0, 1);
  qp.set_a(Y, 0, 1); 
  qp.set_b(0, 4);

  qp.set_a(X, 1, 4);
  qp.set_a(Y, 1, 2);
  qp.set_b(1, a * b);


  qp.set_a(X, 2, -1);
  qp.set_a(Y, 2, 1);
  qp.set_b(2, 1);

  qp.set_d(X, X, 2 * a);
  qp.set_c(Y, -b);


  *s = CGAL::solve_quadratic_program(qp, ET());

  assert(s->solves_quadratic_program(qp));
}

void solve_min(Solution *s, int a, int b) {
  Program qp(CGAL::LARGER, false, 0, true, 0);

  const int X = 0;
  const int Y = 1;
  const int Z = 2;

  qp.set_a(X, 0, 1);
  qp.set_a(Y, 0, 1);
  qp.set_a(Z, 0, 0);
  qp.set_b(0, -4);

  qp.set_a(X, 1, 4);
  qp.set_a(Y, 1, 2);
  qp.set_a(Z, 1, 1);
  qp.set_b(1, -a * b);


  qp.set_a(X, 2, -1);
  qp.set_a(Y, 2, 1);
  qp.set_a(Z, 2, 0);
  qp.set_b(2, -1);

  qp.set_d(X, X, 2 * a);
  qp.set_d(Z, Z, 2);
  qp.set_c(Y, b);

  qp.set_u(Z, false);
  qp.set_l(Z, true, 0);

  *s = CGAL::solve_quadratic_program(qp, ET());
  assert(s->solves_quadratic_program(qp));
}

int main() {

  for (;;) {
    int p;
    cin >> p;

    if (!p) {
      break;
    }

    int a, b;

    cin >> a >> b;

    Solution s;
    if (p == 1) {
      solve_max(&s, a, b);
    } else {
      solve_min(&s, a, b);
    }

    if (s.is_infeasible()) {
      cout << "no\n";
    } else if (s.is_unbounded()) {
      cout << "unbounded\n";
    } else {
      if (p == 1) {
        int res = floor(-CGAL::to_double(s.objective_value()));
        cout << (res == 0 ? 0 : res) << "\n";
      } else {
        int res = ceil(CGAL::to_double(s.objective_value()));
        cout << (res == 0 ? 0 : res) << "\n";
      }
    }
  }


  return 0;
}

