#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <ctime>
#include <cstdlib>

using namespace std;

set<int> sol;
int main() {
  int nr_tests;

  cout << "1\n";
  int n = 1000;
  cout << n << "\n";

  srand(time(0));

  set<int> t;

  for (int i = 0; i < n; i++) {
    int x;
    do {
      x = rand() % 20000 - 10000;
    } while (t.find(x) != t.end());
    t.insert(x);

    cout << x << " ";
  }

  return 0;
}
