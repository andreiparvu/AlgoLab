#include <cstdio>

int main() {
  int nrTests;
  scanf("%d", &nrTests);

  while (nrTests--) {
    int n;

    scanf("%d", &n);

    double sum = 0;

    for (int i = 0; i < n; i++) {
      double x;

      scanf("%lf", &x);

      sum += x;
    }

    printf("%.6lf\n", sum);
  }

  return 0;
}

