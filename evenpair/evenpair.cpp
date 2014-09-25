#include <iostream>

using namespace std;

const int NMAX = 70005;

int even[NMAX], evenSum[NMAX];

int main() {
  int n;
  cin >> n;

  even[0] = 1;
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    int x;

    cin >> x;
    sum += x;

    if (sum % 2 == 0) {
      even[i] = 1;
    }
  }
  for (int i = n; i; i--) {
    evenSum[i] = even[i] + evenSum[i + 1];
  }

  int result = 0;
  for (int i = 1; i <= n; i++) {
    if (even[i - 1] == 1) {
      result += evenSum[i];
    } else {
      result += n - i + 1 - evenSum[i];
    }
  }

  cout << result << "\n";

  return 0;
}

